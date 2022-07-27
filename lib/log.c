#include "log.h"
#include "xtime.h"

FILE *open_log_file(const char *filename)
{
	FILE *logfd = fopen(filename, "a+");
	if (logfd == NULL) {
		fprintf(stderr, "Log File Open Failed.");
		return NULL;
	}

	return logfd;
}


int info(FILE *fd, const char *fmt, ...) 
{
	fprintf(fd, INFO_COLOR "[%s] ", "INFO");
	char strtime[20];
	local_time_str(strtime, "yyyy-mm-dd hh24:mi:ss");

	fprintf(fd, "%s ", strtime);
	
	va_list vl;
	va_start(vl, fmt);
	vfprintf(fd, fmt, vl);
	va_end(vl);

	fprintf(fd, "\n");
	
	fflush(fd);
	return 0;
}

int debug(FILE *fd, const char *fmt, ...)
{
	fprintf(fd, DEBUG_COLOR "[%s] ", "DEBUG");
	char strtime[20];
	local_time_str(strtime, "yyyy-mm-dd hh24:mi:ss");
	fprintf(fd, "%s ", strtime);
	
	va_list vl;
	va_start(vl, fmt);

	vfprintf(fd, fmt, vl);

	va_end(vl);

	fprintf(fd, "\n");
	
	fflush(fd);

	return 0;
}

int error(FILE *fd, const char *fmt, ...) 
{
	fprintf(fd, ERROR_COLOR "[%s] ", "ERROR");
	char strtime[20];
	local_time_str(strtime, "yyyy-mm-dd hh24:mi:ss");
	fprintf(fd, "%s ", strtime);

	va_list vl;
	va_start(vl, fmt);

	vfprintf(fd, fmt, vl);

	va_end(vl);

	fprintf(fd, "\n");
	
	fflush(fd);

	return 0;
}

