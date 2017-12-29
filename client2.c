/* Client program for Internet UDP sockets */
/* From the book of Haviland, pp. 270 
-
271, modified */
/* Read more explanation in this book */
/* Client assumes that the server has  */
/* IP addr = 194.27.78.05 
and port = 7000 */
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
int
main(void)
{
char buf[1024];
int n, s, ns, len;
struct sockaddr_in cli = {AF_INET, INADDR_ANY, INADDR_ANY};
struct sockaddr_in srv = {AF_INET, PORT}; /* For server's address
*/
int cli_len = SIZE;

printf("CLIENT: starting ...\n");
/* Convert and store IP address of the server: 194.27.78.05 (mesarya) */


srv.sin_addr.s_addr = inet_addr("127.0.0.1");

/*
* Create the Internet socket, of SOCK_DGRAM type.
*/

if
((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
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
* Bind the socket to the the IP address of this host.
*/


if (bind(s, (struct sockaddr *) &cli, SIZE) < 0) 
{
perror("bind problem");
exit(1);
}


/*
* Send a message to the socket s*/


n = sendto(s, "This is a request from client\n", 30, 0,(struct sockaddr*)&srv, SIZE);

if (n < 0) {perror("sendto problem"); exit(1);}
printf ("CLIENT: sent a request... and waiting for a reply\n");

n = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&cli, &cli_len);

if (n < 0) {perror("recvfrom problem"); exit(1);}
write(1, buf, n);




/*
* Close the socket and terminate.
*/


close(s);
printf ("... and terminated\n");
exit(0);
}
