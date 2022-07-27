#include "hh.h"

#define ERROR_COLOR "\033[0;32;31m"
#define INFO_COLOR  "\033[0;32;32m"
#define DEBUG_COLOR "\033[m"

// Open logfile and return a FILE*
FILE *open_log_file(const char *filename);

int info(FILE *fd, const char *fmt, ...);
int debug(FILE *fd, const char *fmt, ...);
int error(FILE *fd, const char *fmt, ...);

int backup_log(FILE *fd);

