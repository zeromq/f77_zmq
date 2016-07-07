# ZeroMQ header file

ifndef ZMQ_H
$(error Please set the ZMQ_H environment variable to the full path of zmq.h)
endif

CC=gcc -fPIC 
CFLAGS=-O3 -fPIC -Wall -pedantic -g
#CFLAGS=-O3 -fPIC -g

.PHONY: default

default: libf77zmq.so libf77zmq.a f77_zmq.h

libf77zmq.so: f77_zmq.o
	$(CC) -shared $^ -o $@

libf77zmq.a: f77_zmq.o 
	$(AR) cr $@  $^

zmq.h: $(ZMQ_H)
	cp $(ZMQ_H) .

f77_zmq.o: f77_zmq.c f77_zmq.h
	$(CC) $(CFLAGS) -c f77_zmq.c -o $@

f77_zmq.h: create_f77_zmq_h.py zmq.h f77_zmq.c
	python2 create_f77_zmq_h.py zmq.h || python3 create_f77_zmq_h_py3.py zmq.h

clean:
	$(RM) -f -- f77_zmq.o f77_zmq.h
	$(MAKE) -C examples clean
