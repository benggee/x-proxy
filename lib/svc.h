#include "hh.h"

typedef struct svc_context {
	FILE *log_fd;
	int  tcpserver_fd;
} svc_ctx;


svc_ctx *init_svc_context();

void init_log(svc_ctx *ctx, const char *filename);
void init_tcpserver(svc_ctx *ctx, const int port);


