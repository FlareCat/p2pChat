#include "../include/server.h"

int main() {
	struct addrinfo hints;
	struct addrinfo *result, *result_ptr;
	int socket_fd, accepted_socket_fd;
	int api_return_val, yes = 1;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	ssize_t no_bytes_read;
	char buffer[MAX_BUFLEN];
	char port_no[8];
	char host[NI_MAXHOST], service[NI_MAXSERV];

	log_init(l, "../");
	fprintf(l, "%s:\n\n", __FILE__);
	
	set_port(port_no);
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC; 			/* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; 		/* TCP sockets */
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV; 	/* Sets up the socket as a server */
	hints.ai_protocol = 0; 				/* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL; 				/* Pointer to the next structure in the linked list (returned by getaddrinfo) */

	api_return_val = getaddrinfo(NULL, port_no, &hints, &result);
	if(0 != api_return_val) {
		log_error(errno, gai_strerror(api_return_val));
	}

	socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if(-1 == socket_fd) {
		log_error(errno, "Could not create the socket.");
	}
	
	if(-1 == setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) {
		log_error(errno, "Something went wrong while trying to make the address re-usable (for multiple bind() calls).");
	}

	if(-1 == bind(socket_fd, result->ai_addr, result->ai_addrlen)) {
		log_error(errno, "Could not bind the address to the socket.");
	}

	freeaddrinfo(result);

	/* SOMAXCONN = 128 = max number of connections that can be queued */
	if(-1 == listen(socket_fd, SOMAXCONN)) {
		log_error(errno, "An error occurred while trying to mark the socket to allow for accepting incoming connections.");
	}

	/* Infinitely wait for client connections */

	while(1) {
		fprintf(l, "Waiting for a connection...\n");
		peer_addr_len = 0;
		
		accepted_socket_fd = accept(socket_fd, (struct sockaddr *)&peer_addr, &peer_addr_len);
		if(-1 == accepted_socket_fd) {
			log_error(errno, "An error occurred while trying to accept an incoming connection.");
		}

		getpeername(accepted_socket_fd, (struct sockaddr *)&peer_addr, &peer_addr_len);
		
		memset(host, '\0', NI_MAXHOST);
		memset(service, '\0', NI_MAXSERV);
		getnameinfo((struct sockaddr *)&peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);
		fprintf(l, "Connected to %s:%s\nWaiting for data...\n", host, service);
		no_bytes_read = read(accepted_socket_fd, buffer, MAX_BUFLEN);
		
		fprintf(l, "Read %d bytes:\n%s\n\n", no_bytes_read, buffer);
		close(accepted_socket_fd);
	}
	close(socket_fd);
	fclose(l);

	return EXIT_SUCCESS;
}
