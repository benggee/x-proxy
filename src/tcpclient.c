#include "tcpclient.h"
#include "log.h"

int client_connect(svc_ctx *ctx, const char *ip, const unsigned int port) 
{
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		error(ctx->log_fd, "Socket failed.");
		return -1;
	}

	struct hostent *h;
	if ((h = gethostbyname(ip)) == 0) {
		close(sockfd);
		return -1;
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);

	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return sockfd;
}
