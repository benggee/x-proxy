#include "hh.h"
#include "route.h"
#include "log.h"

int proxy_run(svc_ctx *ctx);

int accept_connect_to_dst(svc_ctx *ctx, struct epoll_event *epoll_evs, const int epoll_fd);

int create_timerfd(svc_ctx *ctx, const int epoll_fd);

int timerfd_check(svc_ctx *ctx, const int epoll_fd);

int forward(svc_ctx *ctx, const int from_fd, const int to_fd);
