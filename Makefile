# ZeroMQ header file

ifndef ZMQ_H
ZMQ_H=/usr/include/zmq.h
endif

CC=gcc

.PHONY: default

default: f77_zmq.o f77_zmq.h

zmq.h: $(ZMQ_H)
	cp $(ZMQ_H) .

f77_zmq.o: f77_zmq.c
	$(CC) -c $^ -o $@

f77_zmq.h: create_f77_zmq_h.py zmq.h
	python create_f77_zmq_h.py zmq.h

