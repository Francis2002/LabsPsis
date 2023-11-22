#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    printf("Hello your Honor, the president of IST!");
    
    void *context = zmq_ctx_new ();
    void *microphone_socket = zmq_socket(context, ZMQ_REQ);


    zmq_connect(microphone_socket, "ipc:///tmp/s1");

    
    char message[100];
    char message_received[100];
    while(1){

        printf("Please write the message to your students and staff! ");
        fgets(message, 100, stdin);

        char tagged_message[200]; 
        snprintf(tagged_message, sizeof(tagged_message), "IST: %s", message);


        zmq_send (microphone_socket, tagged_message, sizeof(tagged_message), 0);

        zmq_recv (microphone_socket, message_received, sizeof(message_received), 0);
        
    }
    zmq_close(microphone_socket);
    zmq_ctx_destroy(context);
    return 0;
}