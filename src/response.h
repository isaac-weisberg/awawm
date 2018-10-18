#ifndef RESPONSE_H
#define RESPONSE_H

typedef struct {

} Response;

int response_serialize(Response* response, char** tcpResponse_ptr, int* tcpResponseLength_ptr);

#endif
