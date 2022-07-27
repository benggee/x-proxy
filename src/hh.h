#ifndef  __HH__
#define  __HH__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXSOCK 	1024
#define MAXROUTE 	128

int clientsocks[MAXSOCK];
int clientatime[MAXSOCK];

typedef struct proxy_route {
	int 	listenport;		// listen port for locate
	char 	dstip[31];		// dst ip
	int 	dstport;		// dst port
	int 	listensock;		// locate socket
} pr_route;

typedef struct svc_context {
	FILE *log_fd;
	int  tcpserver_fd;
	pr_route proxy_routes[MAXROUTE];
} svc_ctx;


struct itimerspec timeout;

#endif

