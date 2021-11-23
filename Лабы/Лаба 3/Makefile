CC=gcc
CFLAGS=-Wall
CXX=g++
CXXFLAGS=-Wall
PROJECT=queue


all: $(PROJECT)

svr4_queue.o: svr4_queue.c svr4_queue.h
	$(CC) $(CFLAGS) -c svr4_queue.c -o $@

main.o: main.cpp svr4_queue.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

$(PROJECT): main.o svr4_queue.o
	$(CXX) $(CXXFLAGS) main.o svr4_queue.o -o $@ 

