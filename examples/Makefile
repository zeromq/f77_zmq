FC=ifort -O2 -xHost
FC=gfortran -g -O0 -Wall -Wno-unused
LIBS=-lzmq #-L$(ZMQ_ROOT)/src/.libs 

EXE=hwserver hwclient wuserver wuclient ventserver ventclient\
    hwserver_msg hwclient_msg

.PHONY: default

default: $(EXE)

%: %.f f77_zmq.h f77_zmq.o
	$(FC) $*.f -o $@ f77_zmq.o $(LIBS)

f77_zmq.o: ../f77_zmq.o
	cp ../f77_zmq.o .

f77_zmq.h: ../f77_zmq.h
	cp ../f77_zmq.h .

clean:
	$(RM) -f -- $(EXE) f77_zmq.o f77_zmq.h *.ipc
