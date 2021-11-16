ACLOCAL_AMFLAGS = -I build-config/m4

lib_LTLIBRARIES = libf77zmq.la
include_HEADERS = f77_zmq.h f77_zmq_free.h
libf77zmq_la_SOURCES = f77_zmq.c $(include_HEADERS)

CLEANFILES = $(include_HEADERS)

MISSING=$(srcdir)/build-config/missing

f77_zmq.h: f77_zmq.c $(srcdir)/create_f77_zmq_h.py
	$(MISSING) python $(srcdir)/create_f77_zmq_h.py $(srcdir)/f77_zmq.c

f77_zmq_free.h: f77_zmq.h





# Examples
# --------

exampledir = $(docdir)/examples
example_DATA = \
    examples/hwclient.f          \
    examples/hwclient_msg.f      \
    examples/hw_msg.sh           \
    examples/hwserver.f          \
    examples/hwserver_msg.f      \
    examples/hw.sh               \
    examples/Makefile            \
    examples/python_client.f     \
    examples/python_server.py    \
    examples/shell_functions.sh  \
    examples/socket_monitor.sh   \
    examples/ventclient.f        \
    examples/ventserver.f        \
    examples/vent.sh             \
    examples/vent_thread.f       \
    examples/wuclient.f          \
    examples/wuserver.f          \
    examples/wu.sh


# Tests
# -----

TESTS = examples/test_build.sh


check_PROGRAMS =                 \
    examples/hwserver            \
    examples/hwclient            \
    examples/wuserver            \
    examples/wuclient            \
    examples/ventserver          \
    examples/ventclient          \
    examples/python_client       \
    examples/hwserver_msg        \
    examples/hwclient_msg        \
    examples/vent_thread

EXTRA_DIST =                     \
    create_f77_zmq_h.py          \
    examples/hw_msg.sh           \
    examples/hw.sh               \
    examples/python_server.py    \
    examples/socket_monitor.sh   \
    examples/shell_functions.sh  \
    examples/test_build.sh       \
    examples/vent.sh             \
    examples/Makefile            \
    examples/wu.sh


TESTLDADD =  -lf77zmq $(ZMQ_LIBS) -L$(builddir)
TESTLDFLAGS = -no-install
TESTFFLAGS = -I$(builddir) -I$(srcdir)

export abs_builddir

examples_hwserver_SOURCES       =  examples/hwserver.f
examples_hwserver_LDADD         =  $(TESTLDADD)
examples_hwserver_LDFLAGS       =  $(TESTLDFLAGS)
examples_hwserver_FFLAGS       =  $(TESTFFLAGS)

examples_hwclient_SOURCES       =  examples/hwclient.f
examples_hwclient_LDADD         =  $(TESTLDADD)
examples_hwclient_LDFLAGS       =  $(TESTLDFLAGS)
examples_hwclient_FFLAGS       =  $(TESTFFLAGS)

examples_wuserver_SOURCES       =  examples/wuserver.f
examples_wuserver_LDADD         =  $(TESTLDADD)
examples_wuserver_LDFLAGS       =  $(TESTLDFLAGS)
examples_wuserver_FFLAGS       =  $(TESTFFLAGS)

examples_wuclient_SOURCES       =  examples/wuclient.f
examples_wuclient_LDADD         =  $(TESTLDADD)
examples_wuclient_LDFLAGS       =  $(TESTLDFLAGS)
examples_wuclient_FFLAGS       =  $(TESTFFLAGS)

examples_ventserver_SOURCES     =  examples/ventserver.f
examples_ventserver_LDADD       =  $(TESTLDADD)
examples_ventserver_LDFLAGS     =  $(TESTLDFLAGS)
examples_ventserver_FFLAGS     =  $(TESTFFLAGS)

examples_ventclient_SOURCES     =  examples/ventclient.f
examples_ventclient_LDADD       =  $(TESTLDADD)
examples_ventclient_LDFLAGS     =  $(TESTLDFLAGS)
examples_ventclient_FFLAGS     =  $(TESTFFLAGS)

examples_python_client_SOURCES  =  examples/python_client.f
examples_python_client_LDADD    =  $(TESTLDADD)
examples_python_client_LDFLAGS  =  $(TESTLDFLAGS)
examples_python_client_FFLAGS  =  $(TESTFFLAGS)

examples_hwserver_msg_SOURCES   =  examples/hwserver_msg.f
examples_hwserver_msg_LDADD     =  $(TESTLDADD)
examples_hwserver_msg_LDFLAGS   =  $(TESTLDFLAGS)
examples_hwserver_msg_FFLAGS   =  $(TESTFFLAGS)

examples_hwclient_msg_SOURCES   =  examples/hwclient_msg.f
examples_hwclient_msg_LDADD     =  $(TESTLDADD)
examples_hwclient_msg_LDFLAGS   =  $(TESTLDFLAGS)
examples_hwclient_msg_FFLAGS   =  $(TESTFFLAGS)

examples_vent_thread_SOURCES    =  examples/vent_thread.f
examples_vent_thread_LDADD      =  $(TESTLDADD)
examples_vent_thread_LDFLAGS    =  $(TESTLDFLAGS)
examples_vent_thread_FFLAGS    =  $(TESTFFLAGS)





