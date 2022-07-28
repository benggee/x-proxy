#include "route.h"

int parse_route(svc_ctx *ctx, const char *conf_file) 
{	
	for (int i = 0; i < MAXROUTE; i++) {
		ctx->proxy_routes[i].listenport = -1;
	}

	FILE *fd = fopen(conf_file, "r");
	if (fd == NULL) {
		return -1;
	}

	int idx = 0;
	while(1) {
		char linebuf[1024];	
		if (fgets(linebuf, sizeof(linebuf), fd) == NULL) {
			break;
		}

		char **res = str_split(linebuf, ' ', 3, 1024);
		if (res == NULL) {
			continue;
		}

		ctx->proxy_routes[idx].listenport = atoi(res[0]);
		strcpy(ctx->proxy_routes[idx].dstip, res[1]);
		ctx->proxy_routes[idx].dstport = atoi(res[2]);
		ctx->proxy_routes[idx].listensock = init_tcp_server(atoi(res[0]));

	}

	return 0;
}


char **str_split(char *str, const char spit, const int size, const int len)
{
	char **strs = malloc(sizeof(char *) * len * size);

	int slen = strlen(str);
	int idx = 0;
	int readidx = 0;
	char readbuf[slen];

	for (int i = 0; i < slen; i++) {
		if (str[i] == spit) {
			if (idx == size) {
				break;
			}

			readbuf[++readidx] = '\0';
			strs[idx] = malloc(sizeof(char) * slen);
			strcpy(strs[idx], readbuf);
			memset(readbuf, 0, sizeof(readbuf));
			idx++;
			readidx = 0;

			continue;
		}	

		if (str[i] == '\0') {
			break;
		}

		if (readidx > len) {
			break;
		}

		readbuf[readidx] = str[i];
		readidx++;
	}

	if (idx != (size - 1)) {
		for (int i = 0; i < size; i++) {
			free(strs[i]);
		}
		free(strs);

		return NULL;
	}
	readbuf[++readidx] = '\0';
	strs[idx] = malloc(sizeof(char) * slen);
	strcpy(strs[idx], readbuf);

	return strs;
}
