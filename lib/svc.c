#include "svc.h"
#include "log.h"
#include "tcpserver.h"

svc_ctx *init_svc_context() 
{
	void *svc = malloc(sizeof(svc_ctx));
	return (svc_ctx *)svc; 
}

void init_log(svc_ctx *ctx, const char *filename)
{
	FILE *fd = open_log_file(filename);
	if (fd == NULL) {
		fprintf(stderr, "Open log file failed.");
		exit(0);
	}
	
	ctx->log_fd = fd;
}

void init_tcpserver(svc_ctx *ctx, const int port) 
{
	int listen_fd = init_tcp_server(port);
	if (listen_fd <= 0) {
		exit(0);
	} 
	ctx->tcpserver_fd = listen_fd;
}
