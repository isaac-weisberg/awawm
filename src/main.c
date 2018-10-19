#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include "accumulate.h"
#include "request.h"
#include "response.h"
#include "routing.h"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        int error = errno;
        printf("Socket error: %d\n", error);
    } 

    struct sockaddr_in endpoint;
    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(8080);
    endpoint.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindingResult = bind(fd, (struct sockaddr*)&endpoint, sizeof(endpoint));
    if (bindingResult == -1) {
        int error = errno;
        printf("Binding error: %d\n", error);
    }
    
    int listenResult = listen(fd, 35);
    if (listenResult == -1) {
        int error = errno;
        printf("Listen error: %d\n", error);
    }

    printf("Listening for connections.\n");
    
    int connfd = accept(fd, NULL, NULL);
    if (connfd == -1) {
        int error = errno;
        printf("Connection accept error: %d\n", error);
    }

    Request request;
    int accumulationRes = accumulate_request(connfd, &request);
    if (accumulationRes == -1) {
        int error = errno;
        printf("Request accumulation error: %d\n", error);
    }

    Response response;

    int routingResult = route(&request, &response);
    if (routingResult != 0) {
        int error = errno;
        printf("Routing error: %d\n", error);
    }

    char* responseStream;
    int responseLength;
    int serializationResult = response_serialize(&response, &responseStream, &responseLength);
    if (serializationResult != 0) {
        int error = errno;
        printf("Response serialization error: %d\n", error);
    }

    int streamWriteResult = dump_stream(connfd, responseStream, responseLength);
    if (streamWriteResult != 0) {
        int error = errno;
        printf("Response stream write error: %d\n", error);
    }

    int connCloseResult = close(connfd);
    if (connCloseResult != 0) {
        int error = errno;
        printf("Connection closing error: %d\n", error);
    }

    printf("pwogwam end\n");
}