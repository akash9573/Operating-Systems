#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message queue structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;
    char input[100];

    // Generate a unique key
    if ((key = ftok("queuefile", 65)) == -1) {
        perror("ftok error");
        exit(1);
    }

    // Create a message queue and return its identifier
    if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget error");
        exit(1);
    }

    while (1) {
        // Ask user for the type of message to send
        printf("Enter message type (>0): ");
        scanf("%ld", &message.msg_type);
        getchar(); // to catch the newline character

        if (message.msg_type <= 0) {
            printf("Invalid message type. Please enter a positive integer.\n");
            continue;
        }

        // Sender part: sending the message
        printf("Enter message to send (or type 'exit' to quit): ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);
        message.msg_text[strcspn(message.msg_text, "\n")] = 0; // remove newline character

        if (strcmp(message.msg_text, "exit") == 0) {
            break;
        }

        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) { // Send the message
            perror("msgsnd error");
            continue;
        }
        printf("Sent message: %s\n", message.msg_text);

        // Receiver part: receiving the message
        if (msgrcv(msgid, &message, sizeof(message), message.msg_type, 0) == -1) { // Receive the message
            perror("msgrcv error");
            continue;
        }
        printf("Received message: %s\n", message.msg_text);
    }

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl error");
        exit(1);
    }

    printf("Message queue removed. Exiting.\n");

    return 0;
}
