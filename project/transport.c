#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include "transport.h"
#include "consts.h"


// Main function of transport layer; never quits
void listen_loop(int sockfd, struct sockaddr_in* addr, int type,
                 ssize_t (*input_p)(uint8_t*, size_t),
                 void (*output_p)(uint8_t*, size_t)) {
    
    packet pkt;
    if (type == CLIENT) {
        // For client, send SYN
        pkt.seq = htons(rand() % 1000);
        pkt.ack = 0;
        pkt.length = 0;
        pkt.win = htons(MAX_WINDOW);
        pkt.flags = SYN;
        send_packet(sockfd, addr, &pkt);

        // Get the SYN-ACK back
        recv_packet(sockfd, addr, &pkt);
        if (!(pkt.flags & (SYN | ACK))) return;
        uint16_t server_seq = ntohs(pkt.seq);
        
        // Send ACK
        pkt.seq = htons(ntohs(pkt.ack));
        pkt.ack = htons(server_seq + 1);
        pkt.flags = ACK;
        send_packet(sockfd, addr, &pkt);
    }


    while (true) {

    }
}
