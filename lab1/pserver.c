//
//	pserver
//	will accept url from a client and return the webpage
//
//	by Bowen Lyons
//	10/03/19

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFD(char *host, int port);
int errorMsg(const char *type, const char *description);

int main(int argc,char **argv)
{
	// check for command line args
	if (argc != 2) {
		return errorMsg("usage"," pserver <port_number>");
	}
	// get port number from command line arg
	int port_number = atoi(argv[1]);
	// validate port_number
	if (port_number == 0) {
		return errorMsg("atoi","could not atoi argument");
	}
	
	char str[200], wp[40960];
	int listen_fd, conn_fd, n, url_fd;
	struct sockaddr_in servaddr;
	
	/* AF_INET - IPv4 IP , Type of socket, protocol*/
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	// zero out the servaddr struct
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(port_number);
	
	/* Binds the above details to the socket */
	bind(listen_fd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
	/* Start listening to incoming connections */
	listen(listen_fd, 10);
	
	while(1)
	{
		printf("Waiting for connection...\n");
		/* Accepts an incoming connection */
		conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
		printf("Client connected... ");
		bzero(str, sizeof(str)); // zero out string
		// add check to validate http format of url
		// read and output the url from the client
		if (n = read(conn_fd, str, sizeof(str)) > 0) {
			printf("Incoming request for url: %s\n", str);
		}
		printf("Sending request... ");
		url_fd = getFD(str, 80);
		write(url_fd, "GET /\r\n", strlen("Get /\r\n"));
		bzero(wp, sizeof(wp));
		printf("Getting webpage... ");
		read(url_fd, wp, 40959);
		printf("Sending to client... ");
		write(conn_fd, wp, strlen(wp)); // write to the client
		printf("Closing connection...\nGoodbye.\n");
		close (conn_fd); //close the connection
		break;
	}
	return 1;
}
int errorMsg(const char *type, const char *description)
{
	printf("ERROR! %s: %s\n", type, description);
	return 1;
}
// returns socket fd for url at port specified
int getFD(char *url, int port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int sock;
	
	hp = gethostbyname(url);
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	return sock;
}
