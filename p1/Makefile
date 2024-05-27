CC = g++
CFLAGS = 
LDFLAGS = -lstdc++

all: p1

p1: MainTTT.o
	$(CC) $(CFLAGS) $(LDFLAGS) MainTTT.o -o p1

MainTTT.o: MainTTT.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f MainTTT.o p1

