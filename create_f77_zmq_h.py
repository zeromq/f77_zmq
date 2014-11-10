#!/usr/bin/env python

# The first argument is the location of the ZeroMQ source directory

import sys

if len(sys.argv) != 2:
  print "usage: %s zmq.h"
  sys.exit(1)

ZMQ_H = sys.argv[1]

def create_lines(f):
  result = f.read()
  result = result.replace('\\\n', '')
  result = result.split('\n')
  return result

def create_dict_of_defines(lines):
  """lines is a list of lines coming from the zmq.h"""
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
  return d

def print_fortran(d,out):
  keys = list( d.keys() )
  keys.sort()
  for k in keys:
    print >>out, "      integer %s"%(k)
  for k in keys:
    print >>out, "      parameter ( %s = %s )"%(k, d[k])


def main():
  f = open( ZMQ_H, 'r' )
  lines = create_lines(f)
  f.close()
  d = create_dict_of_defines(lines)
  file = open('f77_zmq.h','w')
  print_fortran(d,file)
  file.close()


if __name__ == '__main__':
  main()
