#FC=ifort -O2 -xHost -openmp
FC=gfortran -g -O2 -Wall -Wno-unused -fopenmp
LIBS=libf77zmq.a -lzmq 

EXE=hwserver hwclient wuserver wuclient ventserver ventclient python_client\
    hwserver_msg hwclient_msg vent_thread

.PHONY: default

default: $(EXE)

%: %.f f77_zmq.h libf77zmq.a
	$(FC) $*.f -o $@ $(LIBS)

libf77zmq.a: ../libf77zmq.a
	$(MAKE) -C ..
	cp ../libf77zmq.a .

f77_zmq.h: ../f77_zmq.h
	cp ../f77_zmq.h .

clean:
	$(RM) -f -- $(EXE) f77_zmq.o f77_zmq.h *.ipc
