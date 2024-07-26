# Compiler definitions
CC = gcc
CXX = g++
CFLAGS = -Wall -O2 -I. -I/usr/include
LDFLAGS = -lpcap

# Target executable
TARGET = pcap-test
# Object files
OBJS = pcap-test.o pcap-test-c.o

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile pcap-test.cpp
pcap-test.o: pcap-test.cpp pcap-test.h
	$(CXX) $(CFLAGS) -c $<

# Compile pcap-test.c
pcap-test-c.o: pcap-test.c pcap-test.h
	$(CC) $(CFLAGS) -c pcap-test.c -o pcap-test-c.o

# Clean target to remove generated fils
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
