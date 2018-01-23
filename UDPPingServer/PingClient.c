* CS480, Spring 2016
*
* Simple UDP client, to demonstrate use of the sockets API
* Compile with:
* gcc −Wall −o udp−client udp−client.c
* or
* gcc −g −Wall −o udp−client udp−client.c # to support debugging
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <limits.h>

void handle_error(const char* s)
{
 perror(s);
 exit(1);
}
    int main(int argc, char** argv)
    {
        int sock_fd;
        struct sockaddr_in addr;
        struct hostent* hostentp;
        unsigned int portl;
        unsigned short port;
        size_t num_to_send;
        size_t num_sent;
        
        if (argc != 4)
        {
            fprintf(stderr, "usage: %s <hostname> <port> <message>\n", argv[0]);
        }

        /* convert from string to int */
        portl = strtol(argv[2], &endptr, 10);
        if (endptr == NULL || portl == 0)
        handle_error("strtol");
        assert(portl < USHRT_MAX);
        port = (unsigned short)portl;
      
        if (!(hostentp = gethostbyname(argv[1]))) {
            herror("gethostbyname");
            exit(1);
        }
  
        if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            handle_error("socket");

        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        memcpy(&addr.sin_addr.s_addr,
        hostentp−>h_addr_list[0],
        sizeof(struct in_addr));
        addr.sin_port = htons(port);

        printf("I am about to send %s to IP address %s and port %d\n",
        argv[3], inet_ntoa(addr.sin_addr), atoi(argv[2]));
        num_to_send = strlen(argv[3]);
        num_sent = sendto(sock_fd, /* socket */argv[3], /* buffer to send */num_to_send, /* number of bytes to send */0, /* flags=0: bare−bones use case*/
                          (const struct sockaddr*)&addr, /* the destination */sizeof(addr)); /* size of the destination struct */
       
        if (num_sent != num_to_send) {
            assert(num_sent < 0);
            handle_error("sendto");
            }
        printf("I just sent the bytes!\n");
    98 exit(0);
