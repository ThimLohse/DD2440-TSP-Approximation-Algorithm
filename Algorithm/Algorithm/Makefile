#Makefile for "tsp" c++ application
#Created by Thim Lohse
PROG = tsp
CC = g++
CPPFLAGS = -std=c++11 -Wno-c++98-compat
OBJS = main.o func.o graph.o

tsp: $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	make fresh

main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
func.o:	func.hpp
	$(CC) $(CPPFLAGS) -c func.cpp
graph.o:	Graph.hpp
	$(CC) $(CPPFLAGS) -c Graph.cpp
clean:
	rm -f core $(PROG) $(OBJS)
fresh:
	rm -f core $(OBJS)
