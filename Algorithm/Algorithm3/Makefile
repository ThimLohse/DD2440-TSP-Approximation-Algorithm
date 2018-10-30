#Make file for Traveling Salesman Problem c++ algorithm
#Created by Thim Lohse, lohse@kth.se
PROG = tsp_opt
CC = g++
CPPFLAGS = -std=c++11 -Wno-c++98-compat
OBJS = main.o

tsp: $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	make rm_objs
main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
clean:
	rm -f core $(PROG) $(OBJS)
rm_objs:
	rm -f core $(OBJS)
