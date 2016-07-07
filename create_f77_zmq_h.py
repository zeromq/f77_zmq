#!/usr/bin/env python
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

import sys

if __name__ == '__main__':
  if sys.version_info >= (3, 0):
    import create_f77_zmq_h_py3 as x
  else:
    import create_f77_zmq_h_py2 as x
  x.main()

