# ZeroMQ header file

CC=gcc -fPIC 
CFLAGS=-O3 -Wall -pedantic -g
PREFIX=/usr/local/

.PHONY: default

default: libf77zmq.so libf77zmq.a f77_zmq.h

install: libf77zmq.so libf77zmq.a f77_zmq.h
	install -D -m 644 libf77zmq.a $(PREFIX)/lib/ 
	install -D -m 644 libf77zmq.so $(PREFIX)/lib/ 
	install -D -m 644 f77_zmq.h $(PREFIX)/include/ 
	install -D -m 644 f77_zmq_free.h $(PREFIX)/include/ 

libf77zmq.so: f77_zmq.o
	$(CC) -shared $^ -o $@

libf77zmq.a: f77_zmq.o 
	$(AR) cr $@  $^

f77_zmq.o: f77_zmq.c f77_zmq.h
	$(CC) $(CFLAGS) -c f77_zmq.c -o $@

f77_zmq.h: create_f77_zmq_h.py f77_zmq.c
	python3 create_f77_zmq_h.py 

clean:
	$(RM) -f -- f77_zmq.o f77_zmq.h
	$(MAKE) -C examples clean
