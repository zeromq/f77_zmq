F77\_ZMQ
========
[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/scemama/f77_zmq?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A Fortran 77 binding library for [ZeroMQ](http://zeromq.org)

Usage
-----

Copy the `f77_zmq.h` and `f77_zmq.o` files into your project.

In your Makefile, compile as follows:

```
$(FC) -o $(TARGET) $(OBJ) f77_zmq.o -lzmq
```

Be sure that `libzmq.so.4` is present in your `LD_LIBRARY_PATH` before executing the program.


Installation instructions
-------------------------

Python >= 2.6 is required to create the `f77_zmq.h` file.

Set the `ZMQ_H` environment variable to the absolute path of the zmq.h file, and run make.
The default compiler is gcc.

For example:

```
$ export ZMQ_H=/usr/include/zmq.h
$ make
```

