#include "hh.h"
#include "svc.h"
#include "tcpserver.h"

int parse_route(svc_ctx *ctx, const char *conf_file);

char **str_split(char *str, const char spit, const int size, const int slen);
