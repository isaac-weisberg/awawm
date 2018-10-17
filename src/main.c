#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include "accumulate.h"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        int error = errno;
        printf("Socket error: %d", error);
    } 

    struct sockaddr_in endpoint;
    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(8080);
    endpoint.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindingResult = bind(fd, (struct sockaddr*)&endpoint, sizeof(endpoint));
    if (bindingResult == -1) {
        int error = errno;
        printf("Binding error: %d", error);
    }
    
    int listenResult = listen(fd, 35);
    if (listenResult == -1) {
        int error = errno;
        printf("Listen error: %d", error);
    }

    printf("Listening for connections.\n");
    
    int connfd = accept(fd, NULL, NULL);
    if (connfd == -1) {
        int error = errno;
        printf("Conenction accept error: %d", error);
    }


    char* stream;
    int length;
    int accumulationRes = accumulate_stream(connfd, &stream, &length);
    if (accumulationRes == -1) {
        int error = errno;
        printf("Stream accumulation error: %d", error);
    }

    printf("What we have got is stream of length %d with the following contents:\n%s\n", length, stream);

    printf("pwogwam end\n");
}