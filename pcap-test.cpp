#include "pcap-test.h"
#include <iostream>

int main(int argc, char *argv[]) {
	// Check if the correct number of arguments are provided
	if (argc != 2) 	{
		std::cerr << "syntax: pcap-test <interface>" << std::endl;
		std::cerr << "sampel: pcap=test wlan0" << std::endl;
		return 1;
	}

	// Get the network interface from the command line arguments
	char *dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;

	// Open the specified network interface for packet capture
	// BUFSIZE is a constant for the default buffer size (usually 8192 bytes)
	// 1 means to put the interface in promiscous mode
	// 1000 is the timeout in millieseconds
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == nullptr)	{
		std::cerr << "Couldn't open device " << dev << " : " << errbuf << std::endl;
		return 2;
	}

	// Start capturing packets and process them with the packetHandler function
	// 0 means to capture indefinitely
	pcap_loop(handle, 0, packetHandler, nullptr);

	// Close the network interface
	pcap_close(handle);
	return 0;
}
