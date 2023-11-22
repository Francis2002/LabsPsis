#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    char line[100];
    char dpt_name[100];
    printf("What is the department of this building? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", dpt_name);
    printf("We will broadcast all messages from the president of IST and %s\n", dpt_name);


    void *context = zmq_ctx_new ();
    void *speaker_socket = zmq_socket(context, ZMQ_SUB);

    zmq_connect(speaker_socket, "tcp://localhost:5556");
    zmq_setsockopt(speaker_socket, ZMQ_SUBSCRIBE, dpt_name, 0);
    zmq_setsockopt(speaker_socket, ZMQ_SUBSCRIBE, "Ist President", 0);
    

    char message[100];
    while(1){
        char *type = s_recv (speaker_socket);

        char *string = s_recv (speaker_socket);
        printf("recevd message - %s\n", string);
        free(string);
        free(type);
    }
    zmq_close(speaker_socket);
    zmq_ctx_destroy(context);

    return 0;
}