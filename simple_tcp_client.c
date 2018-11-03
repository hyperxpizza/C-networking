#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
    //check if 3 args
    if(argc != 3)
    {
        fprintf(stderr, "%s <hostname> <port>\n", argv[0]);
        return 1;
    } 
    
    //structs and other variables that we need
    struct hostent *hn;
    struct sockaddr_in server;
    char buffer[512]; // data buffer 
    int client_socket;
    int port = atoi(argv[2]); //port - char to int

    //get ip from dns
    hn = gethostbyname(argv[1]);
    if(hn == NULL)
    {
        fprintf(stderr, "gethostbyname\n");
        return 1;
    }
  
    client_socket = socket(AF_INET, SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = *((unsigned long *)hn->h_addr);
    memset(&(server.sin_zero), '\0', 8);

    //connect to the server
    if(connect(client_socket, (struct sockaddr*)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "connect\n");
        return 1;
    }
    //recieve data   
    if(recv(client_socket, buffer, sizeof(buffer), 0) == -1)
    {
        fprintf(stderr, "recv\n");
        return 1;
    }
    //print out the data
    printf("%s\n",buffer);
    //close the connection
    close(client_socket);

    return 0;

}