#include "../include/client.h"
int main(){
	struct addrinfo hints;
	struct addrinfo *result;
	char port_no[8], server_address[30], buffer[MAX_BUFLEN];
	int status;
	int socket_fd; // socket file descriptor

	log_init(l, "../");
	set_port(port_no);
	set_server(server_address);
	
	//ensuring hints is empty and calling getaddrinfo()
	memset(&hints, 0, sizeof(struct addrinfo));	
	
	//filling in hints with required values
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((status = getaddrinfo(server_address, port_no, &hints, &result ))!=0){
		log_error(errno, gai_strerror(status));
	}
	
	if((socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1)	{
		log_error(errno, "Error creating socket to server.");
	}
	
	fprintf(l, "%d\n", result->ai_addrlen);
	if(connect(socket_fd, result->ai_addr, result->ai_addrlen)==-1){
		log_error(errno, "Error connecting!\n");
	}
	// sending sample data to buffer
	strcpy(buffer,"amalantony@gmail.com");
	write(socket_fd, buffer, MAX_BUFLEN);
}
