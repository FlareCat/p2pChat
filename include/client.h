#ifndef _CLIENT_H 		/* Ensures that this header is included only once */
#define _CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "log.h"

#define MAX_BUFLEN 1024

#define set_port(s) \
	strcpy(s, "60000")

#define set_server(s) \
	strcpy(s, "127.0.0.1")

#endif
