#include "log.h"
#include "tcpserver.h"
#include "svc.h"
#include "route.h"
#include "proxy.h"

int main()
{
	svc_ctx *ctx = init_svc_context();

	init_log(ctx, "/tmp/test.log");
	init_tcpserver(ctx, 3003);
	test_route(ctx);

	proxy_run(ctx);


	info(ctx->log_fd, "tcp server listend at: %d, listenfd: %d", 3003, ctx->tcpserver_fd);

	return 0;
}
