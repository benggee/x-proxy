#include "route.h"

int parse_conf(svc_ctx *ctx, const char *conf_file) 
{
	return 0;
}


int test_route(svc_ctx *ctx) {
	for (int i = 0; i < MAXROUTE; i++) {
		ctx->proxy_routes[i].listenport = -1;
	}

	ctx->proxy_routes[0].listenport = 5005;
	strcpy(ctx->proxy_routes[0].dstip, "127.0.0.1");
	ctx->proxy_routes[0].dstport = 3003;
	ctx->proxy_routes[0].listensock = init_tcp_server(5005);
	
	return 0;
}
