# # make file for the project
# # mync.cpp is the main file for the project
# # Parcer.cpp, TCPhandler.cpp, UDPhandler.cpp, are the hallper files for the project

# # Compiler
# CC = g++

# # Compiler flags
# CFLAGS = -Wall -std=c++11


# all: mync

# mync: Parser.o TCPhandler.o UDPhandler.o mync.o 
# 	$(CC) $(CFLAGS) -o $(TARGET) Parser.o TCPhandler.o UDPhandler.o mync.o

# # Compile
# Parser.o: Parser.cpp Parser.hpp
# 	$(CC) $(CFLAGS) -c Parser.cpp

# TCPhandler.o: TCPhandler.cpp
# 	$(CC) $(CFLAGS) -c TCPhandler.cpp

# UDPhandler.o: UDPhandler.cpp
# 	$(CC) $(CFLAGS) -c UDPhandler.cpp

# mync.o: mync.cpp Parser.hpp
# 	$(CC) $(CFLAGS) -c mync.cpp

# # Clean
# clean:
# 	rm -f *.o mync


# Makefile for the project
# mync.cpp is the main file for the project
# Parser.cpp, TCPhandler.cpp, UDPhandler.cpp are the helper files for the project

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Target executable name
TARGET = mync

all: $(TARGET)

$(TARGET): Parser.o TCPhandler.o UDPhandler.o mync.o 
	$(CC) $(CFLAGS) -o $@ Parser.o TCPhandler.o UDPhandler.o mync.o

# Compile
Parser.o: Parser.cpp Parser.hpp
	$(CC) $(CFLAGS) -c Parser.cpp

TCPhandler.o: TCPhandler.cpp TCPhandler.hpp
	$(CC) $(CFLAGS) -c TCPhandler.cpp

UDPhandler.o: UDPhandler.cpp UDPhandler.hpp
	$(CC) $(CFLAGS) -c UDPhandler.cpp

mync.o: mync.cpp Parser.hpp
	$(CC) $(CFLAGS) -c mync.cpp

# Clean
clean:
	rm -f *.o $(TARGET)
