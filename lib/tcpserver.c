#include "tcpserver.h"

int init_tcp_server(const int port) 
{
	int listen_fd;
	struct sockaddr_in serveaddr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd <= 0) {
		fprintf(stderr, "Socket failed.");
		return -1;
	}

	int opt = 1;
	unsigned int opt_len = sizeof(opt);
	
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len);

	memset(&serveaddr, 0, sizeof(serveaddr));
	serveaddr.sin_family = AF_INET;
	serveaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveaddr.sin_port = htons(port);

	if (bind(listen_fd, (struct sockaddr *)&serveaddr, sizeof(serveaddr)) != 0) {
		fprintf(stderr, "Bind Failed.");
		return -1;
	}

	if (listen(listen_fd, 1024) != 0) {
		fprintf(stderr, "Listen failed.");
		return -1;
	}

	return listen_fd;
}
