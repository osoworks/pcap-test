#ifndef PCAP_TEST_H
#define PCAP_TEST_H

#include <pcap.h>	// For packet capture functions
#include <netinet/in.h>	// For IP address structures and functions
#include <arpa/inet.h>	// For inet_ntoa function to convert IP addresses to strings

// Ethernet header structure
struct ethernet_header {
	uint8_t ether_dhost[6];	// Destination MAC address
	uint8_t ether_shost[6];	// Source MAC address
	uint16_t ether_type;	// Protocol type (IP, ARP, etc)
};

// IPv4 header structure
struct ipv4_header {
	uint8_t ip_vhl;		// Version and header length
	uint8_t ip_tos;		// Type of service
	uint16_t ip_len;	// Total length
	uint16_t ip_id;		// Identification
	uint16_t ip_off;	// Fragment offset field
	uint8_t ip_ttl;		// Time to live
	uint8_t ip_p;		// Protocol
	uint16_t ip_sum;	// Checksum
	struct in_addr ip_src;	// Source IP address
	struct in_addr ip_dst;	// Destination IP address
};

// TCP header structure
struct tcp_header {
        uint16_t th_sport;	// Source port
        uint16_t th_dport;	// Destination port
        uint32_t th_seq;        // Sequence number
        uint32_t th_ack;	// Acknowledge number
        uint8_t th_offx2;	// Data offset, rsvd
        uint8_t th_flags;	// Flags
        uint16_t th_win;	// Window
        uint16_t th_sum;	// Checksum
        uint16_t th_urp;	// Urgent pointer
};

#ifdef __cplusplus
extern "C" {
#endif

// Function declaration for the packet handler
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);

#ifdef __cplusplus
}
#endif

#endif	// PCAP_TEST_H
