FC=ifort -O2 -xHost -openmp
#FC=gfortran -g -O2 -Wall -Wno-unused -fopenmp
LIBS=-lzmq 

EXE=hwserver hwclient wuserver wuclient ventserver ventclient\
    hwserver_msg hwclient_msg socket_monitor

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
