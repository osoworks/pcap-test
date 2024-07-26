#include "pcap-test.h"
#include <stdio.h>

// Packet handler function
// This function is called whenever a packet is captured
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
	const struct ethernet_header *eth_header;	// Pointer to Ethernet header
	const struct ipv4_header *ip_header;	// Pointer to IP header
	const struct tcp_header *tcp_header;	// Pointer to TCP header
	const u_char *payload;			// Pointer to payload data
	
	// Point to the Ethernet header
	eth_header = (struct ethernet_header*)(packet);

	// Check if the packet is IP (IPv4)
	if (ntohs(eth_header->ether_type) == 0x0800) {	// 0x0800 is the Ethernet type for IPv4
		// Point to the IP header
		ip_header = (struct ipv4_header*)(packet + sizeof(struct ethernet_header));

		// Check if the packet is TCP
		if (ip_header->ip_p == 6) {	// 6 is the protocol number for TCP
			// Point to the TCP header
			tcp_header = (struct tcp_header*)(packet + sizeof(struct ethernet_header)+sizeof(struct ipv4_header));

			// Point to the payload
			payload = (u_char *)(packet+sizeof(struct ethernet_header)+sizeof(struct ipv4_header)+sizeof(struct tcp_header));

			// Print Source MAC address
			printf("Src MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
					eth_header->ether_shost[0],
					eth_header->ether_shost[1],
					eth_header->ether_shost[2],
					eth_header->ether_shost[3],
					eth_header->ether_shost[4],
					eth_header->ether_shost[5]);

			// Print Destination MAC address
			printf("Dst MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                                        eth_header->ether_dhost[0],
                                        eth_header->ether_dhost[1],
                                        eth_header->ether_dhost[2],
                                        eth_header->ether_dhost[3],
                                        eth_header->ether_dhost[4],
                                        eth_header->ether_dhost[5]);

			// Print Source IP address
			printf("Src IP: %s\n", inet_ntoa(ip_header->ip_src));

			// Print Destination IP address
			printf("Dst IP: %s\n", inet_ntoa(ip_header->ip_dst));

			// Print Source IP number
                        printf("Src Port: %d\n", ntohs(tcp_header->th_sport));

                        // Print Destination IP number
                        printf("Dst Port: %d\n", ntohs(tcp_header->th_dport));

			// Calculate payload length
			int payload_length = pkthdr->len - (sizeof(struct ethernet_header)+sizeof(struct ipv4_header)+sizeof(struct tcp_header));

			// Print payload data (up to 20 bytes)
			if (payload_length > 0) {
				int print_length = payload_length > 20 ? 20 : payload_length;
				printf("Payload: ");
				for (int i=0; i < print_length; i++) {
					printf("%02x ", payload[i]);
				}
				printf("\n");
			} else {
				// If there is no payload data
				printf("Payload: No data\n");
			}
		}
	}
}
