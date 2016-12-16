#!/usr/bin/env python


import zmq
import struct

port=5555

def main():

  context = zmq.Context()
  socket = context.socket(zmq.REP)
  socket.bind("tcp://*:%d" % port)

  # Receive the message from the Fortran
  message = socket.recv()

  nb = len(message)/8   # Number of elements in the array
  data = list( struct.unpack('d'*nb, message) )

  print data

  for i in range(nb):
    data[i] = data[i] + 1.
  message= struct.pack('d'*nb,*data  )

  # Interpret the message as an array of double precision floats
  socket.send(message)




if __name__ == "__main__":
  main()

