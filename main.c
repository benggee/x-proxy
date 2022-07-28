
#include "src/log.h"
#include "src/tcpserver.h"
#include "src/svc.h"
#include "src/route.h"
#include "src/proxy.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: ./xproxy logfile\n");
		printf("sample: ./xproxy /tmp/xproxy.log\n\n");
		return -1;
	}

	svc_ctx *ctx = init_svc_context();

	init_log(ctx, argv[1]);
	// check server status, unimplements.
	// init_tcpserver(ctx, 3005);

	parse_route(ctx, "./proxy.conf");

	printf("X proxy is running...");
	
	proxy_run(ctx);

	return 0;
}
