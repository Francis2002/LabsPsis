#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "zhelpers.h"

int main (void){

    void *context = zmq_ctx_new ();
    void *microphone_socket = zmq_socket(context, ZMQ_REP);

    void *speaker_socket = zmq_socket(context, ZMQ_PUB);


    int rc = zmq_bind(microphone_socket, "ipc:///tmp/s1");
    zmq_bind(speaker_socket, "tcp://*:5556");


    assert (rc == 0);
    while (1) {
        char message_received[200]; 
        zmq_recv (microphone_socket, &message_received, sizeof(message_received), 0);
        char acknowledgment[] = "Message received successfully!";
        zmq_send(microphone_socket, acknowledgment, strlen(acknowledgment), 0);

        printf("%s\n",message_received);
        char *message_data = message_received;
        char *tag = strtok(message_data, ":");
        char *content = strtok(NULL, "");
        if (tag != NULL && content != NULL) {
            if (strcmp(tag, "IST") == 0) {
                s_sendmore(speaker_socket, "Ist President");
                s_send(speaker_socket, content); 
            } else
            {
                s_sendmore(speaker_socket, tag);
                s_send(speaker_socket, content);
            }
        }
    }

    zmq_close(microphone_socket);
    zmq_close(speaker_socket);
    zmq_ctx_destroy(context);
    return 0;
}