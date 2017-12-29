/* Server program for Internet UDP sockets */
/* From the book of Haviland, pp. 269 -270, modified */
/* Read more explanation in this book */
/* Server starts, creates and binds a socket */
/* and, before reading from client, sleeps */
/* for 60 seconds */
/* During this period, the client starts, sends */
/* a request to the server and terminates */
/* After awaiking, the server reads */
/* the client's request and terminates */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#define PORT  7000 /* Port of this server */
#define SIZE sizeof(struct sockaddr_in)


int main(void){
char buf[1024];
int n, s, ns, len;
struct sockaddr_in srv = {AF_INET, PORT, INADDR_ANY};
struct sockaddr_in cli; /* For client's address */

int cli_len = SIZE;
printf("SERVER: starting ...\n");
/** Create the Internet socket, of SOCK_DGRAM type.*/

if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
{
perror("socket problem");
exit(1);
}

/*
* For simplicity, use the IP address as the OS selects.
* It is more preferable to set a specific IP address
* which must be known to all clients...
*/

/*
* Bind the socket to the the IP address of this h
ost.
*/

if (bind(s, (struct sockaddr *) &srv, SIZE) < 0) 
{
perror("bind problem");
exit(1);
}
while(1){
//printf(".... and sleeping during 10 sec ");
printf ("Server is ready to receive requests\n");   

/* Long sleep before reading */
//sleep(10); /* 10 sec */
/*
* Now read from the socket s
*/

n = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&cli, &cli_len);

if (n < 0) {perror("recvfrom problem"); exit(1);}
write(1, buf, n);

char reply[31];
read(0,reply,30);
n = sendto(s, reply, sizeof(reply), 0,(struct sockaddr*)&cli, SIZE);


if (n < 0) {perror("sendto problem"); exit(1);}
printf ("Server: sent a reply... and waiting for the next request\n");



}
printf ("SERVER: terminated...\n");


/*
*
Close the socket and terminate.
*/

close(s);
exit(0);
}
