#include "hh.h"


svc_ctx *init_svc_context();

void init_log(svc_ctx *ctx, const char *filename);
void init_tcpserver(svc_ctx *ctx, const int port);


