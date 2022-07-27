#include "proxy.h"
#include "tcpclient.h"

int proxy_run(svc_ctx *ctx)
{
	int epollfd = epoll_create(1);
	
	struct epoll_event epoll_ev;

	int ter = create_timerfd(ctx, epollfd);
	if (ter <= 0) {
		error(ctx->log_fd, "Create Log failed.");
		return -1;
	}

	struct epoll_event epoll_evs[10];

	while(1) {
		int infds = epoll_wait(epollfd, epoll_evs, 10, -1);
		if (infds < 0) {
			error(ctx->log_fd, "epoll() faild.");
			break;
		}

		for (int i = 0; i < infds; i++) {
			info(ctx->log_fd, "evets=%d, data.fd=%d", epoll_evs[i].events, epoll_evs[i].data.fd);

			if (epoll_evs[i].data.fd == ter) {
				timerfd_settime(ter, 0, &timeout, NULL);

				if (timerfd_check(ctx, epollfd) < 0) {
					error(ctx->log_fd, "timerfd_check failed.");
					break;
				}

				continue;
			}
			
			if (accept_connect_to_dst(ctx, epoll_evs, epollfd) <= 0) {
				continue;
			}
				
			if (forward(ctx, epoll_evs[i].data.fd, clientsocks[epoll_evs[i].data.fd]) < 0) {
				continue;
			}
		}
	}	
	
	return 0;
}

int accept_connect_to_dst(svc_ctx *ctx, struct epoll_event *epoll_evs, const int epoll_fd) 
{
	int i = 0;
	struct epoll_event epoll_ev;

	for (i = 0; i < MAXROUTE; i++) {
		if (ctx->proxy_routes[i].listenport == -1) {
			continue;
		}

		if (epoll_evs[i].data.fd == ctx->proxy_routes[i].listensock) {
			struct sockaddr_in client;
			socklen_t len = sizeof(client);
			int srcsock = accept(ctx->proxy_routes[i].listensock, (struct sockaddr *)&client, &len);
			if (srcsock < 0) break;
			if (srcsock >= MAXSOCK) {
				error(ctx->log_fd, "Connect is max: %d", MAXSOCK);
				break;
			}
			
			debug(ctx->log_fd, "accept client(socket=%d) ok", ctx->proxy_routes[i].listensock);

			int dstsock = client_connect(ctx, ctx->proxy_routes[i].dstip, ctx->proxy_routes[i].dstport);
			if (dstsock < 0) break;
			if (dstsock >= MAXSOCK) {
				error(ctx->log_fd, "Connect is max: %d\n", MAXSOCK);
				close(srcsock);
				break;
			}

			debug(ctx->log_fd, "accept on port(%d) client(%d, %d) ok.", ctx->proxy_routes[i].listenport, srcsock, dstsock);

			epoll_ev.data.fd = srcsock;
			epoll_ev.events = EPOLLIN;
			epoll_ctl(epoll_fd, EPOLL_CTL_ADD, srcsock, &epoll_ev);

			epoll_ev.data.fd = dstsock;
			epoll_ev.events = EPOLLIN;
			epoll_ctl(epoll_fd, EPOLL_CTL_ADD, dstsock, &epoll_ev);

			clientsocks[srcsock] = dstsock;
			clientsocks[dstsock] = srcsock;
			clientatime[srcsock] = time(0);
			clientatime[dstsock] = time(0);

			break;
		}
	}
	
	return 0;
}

int timerfd_check(svc_ctx *ctx, const int epoll_fd) 
{
	for (int i = 0; i < MAXSOCK; i++) {
		if ((clientsocks[i] > 0) && (time(0) - clientatime[i] > 80)) {
			info(ctx->log_fd, "client(%d, %d) timeout.", clientsocks[i], clientsocks[clientsocks[i]]);
			close(clientsocks[i]);
			close(clientsocks[clientsocks[i]]);
			
			clientsocks[clientsocks[i]] = 0;
			clientsocks[i] = 0;
		}
	}	
}

int create_timerfd(svc_ctx *ctx, const int epoll_fd) 
{
	int tfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC);
	if (tfd <= 0) {
		return tfd;
	}

	memset(&timeout, 0, sizeof(struct itimerspec));
	timeout.it_value.tv_sec = 20;
	timeout.it_value.tv_nsec = 0;
	timerfd_settime(tfd, 0, &timeout, NULL);

	struct epoll_event epoll_ev;
	epoll_ev.events = EPOLLIN | EPOLLET;
	epoll_ev.data.fd = tfd;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tfd, &epoll_ev);

	return tfd;
}

int forward(svc_ctx *ctx, const int from_fd, const int to_fd) 
{
	char buffer[1024];
	int  buflen;

	memset(buffer, 0, sizeof(buffer));

	if ((buflen = recv(from_fd, buffer, sizeof(buffer), 0)) <= 0) {
		info(ctx->log_fd, "client(%d, %d) disconnected.", from_fd, to_fd);

		close(from_fd);
		close(to_fd);
		clientsocks[to_fd] = 0;
		clientsocks[from_fd] = 0;

		return -1;
	}

	info(ctx->log_fd, "from %d to %d, %d bytes.", from_fd, to_fd, buflen);
	send(to_fd, buffer, buflen, 0);

	return 0;
}
