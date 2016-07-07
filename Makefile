# ZeroMQ header file

ifndef ZMQ_H
$(error Please set the ZMQ_H environment variable to the full path of zmq.h)
endif

CC=gcc -fPIC 
CFLAGS=-O3 -fPIC -Wall -pedantic -g
#CFLAGS=-O3 -fPIC -g

.PHONY: default

default: libf77zmq.so libf77zmq.a f77_zmq.h

$(ZMQ_H):
	$(error $(ZMQ_H) : file not found)

libf77zmq.so: f77_zmq.o
	$(CC) -shared $^ -o $@

libf77zmq.a: f77_zmq.o 
	$(AR) cr $@  $^

f77_zmq.o: f77_zmq.c f77_zmq.h
	$(CC) $(CFLAGS) -c f77_zmq.c -o $@

f77_zmq.h: create_f77_zmq_h.py $(ZMQ_H) f77_zmq.c
	python create_f77_zmq_h.py $(ZMQ_H)

clean:
	$(RM) -f -- f77_zmq.o f77_zmq.h
	$(MAKE) -C examples clean
