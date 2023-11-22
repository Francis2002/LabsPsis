#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    char line[100];
    char dpt_name[100];
    printf("What is your department? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", dpt_name);
    printf("Hello your Honor, the President of %s\n", dpt_name);

    void *context = zmq_ctx_new ();
    void *microphone_socket = zmq_socket(context, ZMQ_REQ);

    // Connect to the server
    zmq_connect(microphone_socket, "ipc:///tmp/s1");

    
    char message[100];
    char message_received[100];
    while(1){

        printf("Please write the message to the students and staff on your buildings! ");
        fgets(message, 100, stdin);

        char tagged_message[256]; 
        snprintf(tagged_message, sizeof(tagged_message), "[%s] : %s", dpt_name, message);

        zmq_send (microphone_socket, tagged_message, sizeof(tagged_message), 0);

        zmq_recv (microphone_socket, message_received, sizeof(message_received), 0);
        
    }
}