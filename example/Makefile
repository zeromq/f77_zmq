FC=gfortran 
LIBS=-lzmq #-L$(ZMQ_ROOT)/src/.libs 

.PHONY: default

default: server client

server: server.f f77_zmq.h f77_zmq.o
	$(FC) server.f -o $@ f77_zmq.o $(LIBS)

client: client.f f77_zmq.h f77_zmq.o
	$(FC) client.f -o $@ f77_zmq.o $(LIBS)

f77_zmq.o: ../f77_zmq.o
	cp ../f77_zmq.o .

f77_zmq.h: ../f77_zmq.h
	cp ../f77_zmq.h .
