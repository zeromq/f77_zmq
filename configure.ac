# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([f77-zmq], [4.3.3], [https://github.com/zeromq/f77_zmq/issues])
AC_CONFIG_AUX_DIR([build-config])
AC_CONFIG_MACRO_DIRS([build-config/m4])
AM_INIT_AUTOMAKE([silent-rules foreign subdir-objects])

AC_CONFIG_SRCDIR([f77_zmq.c])
AC_CONFIG_HEADERS([build-config/config.h])

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_F77
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


# Checks for libraries.
AX_ZMQ([4.0], [], [ AC_MSG_ERROR([Please install ZeroMQ >= 4.0]) ])

# Required by ZeroMQ
AC_CHECK_HEADERS([stddef.h])
AC_TYPE_INT32_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T



# Checks for header files.
AC_CHECK_HEADERS([memory.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_F77_WRAPPERS

AC_LANG([C])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
