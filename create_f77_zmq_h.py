#!/usr/bin/env python

# The first argument is the location of the ZeroMQ source directory

import sys
import ctypes

if len(sys.argv) != 2:
  print "usage: %s zmq.h"
  sys.exit(1)

ZMQ_H = sys.argv[1]

def create_lines(f):
  result = f.read()
  result = result.replace('\\\n', '')
  result = result.split('\n')
  return result

def create_dict_of_defines(lines,file_out):
  """lines is a list of lines coming from the zmq.h"""
  # Fetch all parameters in zmq.h
  d = {}
  for line in lines:
    if line.startswith("#define"):
      buffer = line.split()
      key = buffer[1]
      value = " ".join(buffer[2:])
      if key[0] == '_' or '(' in key or ',' in value:
        continue
      command = "%(key)s=%(value)s\nd['%(key)s']=%(key)s"%locals()
      exec command in locals()

  # Add the version number:
  d['ZMQ_VERSION'] = ZMQ_VERSION_MAJOR*10000 + ZMQ_VERSION_MINOR*100 + ZMQ_VERSION_PATCH
  d['ZMQ_PTR'] = ctypes.sizeof(ctypes.c_voidp)
  print "==========================================="
  print "ZMQ_PTR set to %d (for %d-bit architectures)"%(d['ZMQ_PTR'],d['ZMQ_PTR']*8)
  print "==========================================="

  # Print to file
  keys = list( d.keys() )
  keys.sort()
  for k in keys:
    print >>file_out, "      integer %s"%(k)
  for k in keys:
    print >>file_out, "      parameter ( %-20s = %s )"%(k, d[k])
  return None

def create_prototypes(lines,file_out):
  """lines is a list of lines coming from the f77_zmq.c file"""
  typ_conv = {
      'int'    : 'integer' ,
      'float'  : 'real', 
      'char*'  : 'character*(*)', 
      'double' : 'double precision', 
      'void*'  : 'integer*%d'%(ctypes.sizeof(ctypes.c_voidp)),
      'void'   : None
      }
  # Get all the functions of the f77_zmq.c file
  d = {}
  for line in lines:
    if line == "":
      continue
    if line[0] in " #{}/":
      continue
    buffer = line.replace('_(','_ (').lower().split()
    typ = typ_conv[buffer[0]]
    if typ is None:
      continue
    name = buffer[1][:-1]
    d[name] = typ

  # Print to file
  keys = list( d.keys() )
  keys.sort()
  for k in keys:
    print >>file_out, "      %-20s %s"%(d[k],k)
  return None



def main():
  file_out = open('f77_zmq.h','w')

  file_in = open( ZMQ_H, 'r' )
  lines = create_lines(file_in)
  file_in.close()

  create_dict_of_defines(lines,file_out)

  file_in = open( 'f77_zmq.c', 'r' )
  lines = create_lines(file_in)
  file_in.close()

  create_prototypes(lines,file_out)

  file_out.close()


if __name__ == '__main__':
  main()
