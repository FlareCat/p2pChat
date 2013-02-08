#ifndef _SERVER_H 		/* Ensures that this header is included only once */
#define _SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "log.h"

#define MAX_BUFLEN 1024

#define set_port(s) \
	strcpy(s, "60000");

#endif
