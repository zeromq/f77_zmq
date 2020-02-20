#!/usr/bin/env python3
#
#    f77_zmq : Fortran 77 bindings for the ZeroMQ library
#    Copyright (C) 2014 Anthony Scemama
#
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#    USA
#
# Anthony Scemama <scemama@irsamc.ups-tlse.fr>
# Laboratoire de Chimie et Physique Quantiques - UMR5626
# Universite Paul Sabatier - Bat. 3R1b4, 118 route de Narbonne
# 31062 Toulouse Cedex 09, France


import re
import os
import sys
import ctypes

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
      try:
        value = int(eval(" ".join(buffer[2:]).strip()))
      except:
        continue
      if key[0] == '_' or '(' in key:
        continue
      d[key] = value
      command = "%(key)s=%(value)d\nd['%(key)s']=%(key)s"%locals()
      command = re.sub("/\*.*?\*/", "", command)
      exec(command, locals())

  # Add the version number:
  d['ZMQ_VERSION'] = int(d['ZMQ_VERSION_MAJOR'])*10000 + int(d['ZMQ_VERSION_MINOR'])*100 + int(d['ZMQ_VERSION_PATCH'])
  d['ZMQ_PTR'] = ctypes.sizeof(ctypes.c_voidp)
  print("===========================================")
  print("ZMQ_PTR set to %d (for %d-bit architectures)"%(d['ZMQ_PTR'],d['ZMQ_PTR']*8))
  print("===========================================")

  # Print to file
  keys = list( d.keys() )
  keys.sort()
  for k in keys:
    print("      integer %s"%(k), file=file_out)
  for k in keys:
    buffer = "      parameter(%s=%s)"%(k, d[k])
    if len(buffer) > 72:
        buffer = "      parameter(\n     & %s=%s)"%(k, d[k])
    print(buffer, file=file_out)

  return None

def create_prototypes(lines,file_out):
  """lines is a list of lines coming from the f77_zmq.c file"""
  typ_conv = {
      'long'   : 'integer*8' ,
      'int'    : 'integer' ,
      'float'  : 'real',
      'char*'  : 'character*(64)',
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
    print("      %-20s %s"%(d[k],k), file=file_out)
    print("      %-20s %s"%("external",k), file=file_out)
  return None



def find_ZMQ_H():
    if "ZMQ_H" is os.environ.keys():
        return os.environ["ZMQ_H"]
    else:
        if "CPATH" in os.environ.keys():
            dirs = os.environ["CPATH"].split(':')
        elif "C_INCLUDE_PATH" in os.environ:
            dirs = os.environ["C_INCLUDE_PATH"].split(':')
        else:
            dirs = ["/usr/include", "/usr/local/include"]
        for d in dirs:
            if d and "zmq.h" in os.listdir(d):
                return ("{0}/zmq.h".format(d))
        return None

def main():

  ZMQ_H = find_ZMQ_H()
  if ZMQ_H is None:
      print("Error: zmq.h not found. You can specify it with the ZMQ_H environment variable")
      sys.exit(1)
  else:
      print("Using {0}".format(ZMQ_H))

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

  file_in  = open('f77_zmq.h','r')
  file_out = open('f77_zmq_free.h','w')
  file_out.write(file_in.read().replace('\n     &',' &\n      '))
  file_in.close()
  file_out.close()



if __name__ == '__main__':
  main()
