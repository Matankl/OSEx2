# make file for the project
# mync.cpp is the main file for the project
# Parcer.cpp, TCPhandler.cpp, UDPhandler.cpp, are the hallper files for the project

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11


all: mync

mync: Parser.o TCPhandler.o UDPhandler.o mync.o
	$(CC) $(CFLAGS) -o $(TARGET) Parser.o TCPhandler.o UDPhandler.o mync.o

# Compile
Parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp

TCPhandler.o: TCPhandler.cpp
	$(CC) $(CFLAGS) -c TCPhandler.cpp

UDPhandler.o: UDPhandler.cpp
	$(CC) $(CFLAGS) -c UDPhandler.cpp

mync.o: mync.cpp
	$(CC) $(CFLAGS) -c mync.cpp

# Clean
clean:
	rm -f *.o mync