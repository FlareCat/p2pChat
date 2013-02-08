#ifndef _LOG_H 		/* Ensures that this header is included only once */
#define _LOG_H

#include <linux/limits.h>
#define LOG_FILE_NAME "log.txt"

FILE *l = NULL;

#define log_init(l, path) { \
	char cmd[PATH_MAX] = "\0"; \
	strcpy(cmd, "touch "); \
	strcat(cmd, path); \
	if(path[strlen(path) - 1] != '/') \
		strcat(path, "/"); \
	strcat(cmd, LOG_FILE_NAME); \
	system(cmd); \
	memset(cmd, '\0', PATH_MAX); \
	strcpy(cmd, path); \
	if(path[strlen(path) - 1] != '/') \
		strcat(path, "/"); \
	strcat(cmd, LOG_FILE_NAME); \
	l = fopen(cmd, "a"); \
	memset(cmd, '\0', PATH_MAX); \
	strcpy(cmd, "date >> "); \
	strcat(cmd, path); \
	if(path[strlen(path) - 1] != '/') \
		strcat(path, "/"); \
	strcat(cmd, LOG_FILE_NAME); \
	system(cmd); \
}

#define log_error(errno, message) { \
	char err_desc[128] = "", temp[128] = ""; \
	if(message != NULL) \
	{ \
		strcpy(err_desc, message); \
		if(message[strlen(message) - 1] != '\n') \
			strcat(err_desc, "\n"); \
	} \
	strerror_r(errno, temp, 128); \
	strcat(err_desc, temp); \
	strcat(err_desc, "\n"); \
	fprintf(l, err_desc); \
	exit(EXIT_FAILURE); \
}

#endif
