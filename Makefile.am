ACLOCAL_AMFLAGS = -I build-config/m4

lib_LTLIBRARIES = libf77zmq.la
include_HEADERS = f77_zmq.h f77_zmq_free.h
libf77zmq_la_SOURCES = f77_zmq.c $(include_HEADERS)

exampledir = $(docdir)/examples
example_DATA = \
 examples/hwclient.f \
 examples/hwclient_msg.f \
 examples/hw_msg.sh \
 examples/hwserver.f \
 examples/hwserver_msg.f \
 examples/hw.sh \
 examples/Makefile \
 examples/python_client.f \
 examples/python_server.py \
 examples/shell_functions.sh \
 examples/socket_monitor.sh \
 examples/ventclient.f \
 examples/ventserver.f \
 examples/vent.sh \
 examples/vent_thread.f \
 examples/wuclient.f \
 examples/wuserver.f \
 examples/wu.sh

CLEANFILES = $(include_HEADERS)

f77_zmq.h: 
	$(PYTHON) create_f77_zmq_h.py

f77_zmq_free.h: f77_zmq.h
