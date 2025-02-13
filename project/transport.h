#pragma once

#include <stdint.h>
#include <unistd.h>

// Main function of transport layer; never quits
void listen_loop(int sockfd, struct sockaddr_in* addr, int type,
                 ssize_t (*input_p)(uint8_t*, size_t),
                 void (*output_p)(uint8_t*, size_t));



#define MSS 1012
typedef struct {
    uint16_t seq;     // Sequence Number
    uint16_t ack;     // Acknowledgment Number
    uint16_t length;  // Payload Length
    uint16_t window;  // Flow Control Window
    uint16_t flags;   // Flags (SYN, ACK, P)
    uint16_t unused;  // Unused Space
    uint8_t payload[MSS];  // Data Payload
} packet;
