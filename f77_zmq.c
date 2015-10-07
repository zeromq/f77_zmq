  /*
    f77_zmq : Fortran 77 bindings for the ZeroMQ library
    Copyright (C) 2014 Anthony Scemama 
    

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA

  Anthony Scemama <scemama@irsamc.ups-tlse.fr>
  Laboratoire de Chimie et Physique Quantiques - UMR5626
  Université Paul Sabatier - Bat. 3R1b4, 118 route de Narbonne
  31062 Toulouse Cedex 09, France
  */

#include "zmq.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>



/* Guidelines
 * ==========
 *
 * + Fortran-callable function names should start with f77_zmq_ and should end with an underscore.
 * + A space should be present between the the name of the function and the '(' character for the
 *   python script to work properly.
 * + void* return types will be translated to INTEGER(ZMQ_PTR)
 * + int   return types will be translated to INTEGER
 *
 */

/* Helper functions *
 * ================ */

int f77_zmq_errno_ (void)
{
  return zmq_errno ();
}

char* f77_zmq_strerror_ (int *errnum)
{
  return (char*) zmq_strerror (*errnum);
}

int f77_zmq_version_ (int *major, int *minor, int *patch)
{
  zmq_version (major, minor, patch);
  return 0;
}

int f77_zmq_microsleep_ (int* microsecs)
{
  struct timespec ts, ts2;
  ts.tv_sec  = 0;
  ts.tv_nsec = 1000L * ( (long) (*microsecs));
  return nanosleep (&ts, &ts2);
}

/* Context *
 * ======= */

void* f77_zmq_ctx_new_ ()
{
    return zmq_ctx_new ();
}

int f77_zmq_ctx_destroy_ (void* *context)
{
    return zmq_ctx_destroy (*context);
}

int f77_zmq_ctx_term_ (void* *context)
{
    return zmq_ctx_term (*context);
}

int f77_zmq_ctx_shutdown_ (void* *context)
{
    return zmq_ctx_shutdown (*context);
}

int f77_zmq_ctx_set_ (void* *context, int* option_name, int* option_value)
{
  return zmq_ctx_set (*context, *option_name, *option_value);
}


/* Sockets *
 * ======= */

void* f77_zmq_socket_ (void* *context, int* type)
{
    return zmq_socket (*context, *type);
}

int f77_zmq_close_ (void* *socket)
{
    return zmq_close(*socket);
}

int f77_zmq_bind_ (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
  }
  address[address_len] = 0;
  rc = zmq_bind (*socket, address);
  free(address);
  return rc;
}

int f77_zmq_unbind_ (void* *socket, char* endpoint, int dummy)
{
  return zmq_unbind(*socket, endpoint);
}


int f77_zmq_connect_ (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
  }
  address[address_len] = 0;
  rc = zmq_connect (*socket, address);
  free(address);
  return rc;
}

int f77_zmq_disconnect_ (void* *socket, char* address, int dummy)
{
  return zmq_disconnect(*socket,address);
}


int f77_zmq_setsockopt_ (void* *socket, int* option_name, void* option_value, int* option_len, int dummy)
{
  return zmq_setsockopt (*socket, *option_name, option_value, *option_len);
}

int f77_zmq_getsockopt_ (void* *socket, int* option_name, void *option_value, int *option_len, int dummy)
{
  size_t option_len_st = (size_t) *option_len;
  return zmq_getsockopt (*socket, *option_name, option_value, &option_len_st);
  *option_len = option_len_st;
}

int f77_zmq_socket_monitor_ (void* *socket, char* address, int* events, int dummy)
{
  return zmq_socket_monitor(*socket,address,*events);
}

/* Send/Recv *
 * ========= */

int f77_zmq_send_ (void* *socket, void* message, int* message_len, int* flags, int dummy)
{
  return zmq_send (*socket, message, *message_len, *flags);
}

int f77_zmq_recv_ (void* *socket, void* message, int* message_len, int* flags, int dummy)
{
  return zmq_recv (*socket, message, *message_len, *flags);
}



/* Messages *
 * ======== */

void* f77_zmq_msg_new_ ()
{
  return malloc (sizeof(zmq_msg_t));
}

int f77_zmq_msg_destroy_ (zmq_msg_t* *msg)
{
  if (*msg != NULL)
  {
    free(*msg);
  }
  return 0;
}

void* f77_zmq_msg_data_new_ (int* size_in, void* buffer, int* size_buffer, int dummy)
{
  void* data = malloc(*size_in * sizeof(char));
  if (*size_buffer > 0)
    memcpy(data,buffer,*size_buffer);
  return data;
}

int f77_zmq_msg_destroy_data_ (void* *data)
{
  if (*data != NULL)
  {
    free(*data);
    data = NULL;
  }
  return 0;
}


int f77_zmq_msg_init_ (zmq_msg_t* *msg)
{
  return zmq_msg_init (*msg);
}


int f77_zmq_msg_close_ (zmq_msg_t* *msg)
{
  return zmq_msg_close (*msg);
}


int f77_zmq_msg_init_size_ (zmq_msg_t* *msg, int* size_in)
{
  size_t size = (size_t) *size_in;
  return zmq_msg_init_size (*msg, size);
}


void ffn(void* data, void* hint)
{
     free(data);
}

int f77_zmq_msg_init_data_ (zmq_msg_t* *msg, void* *data, int* size_in)
{
  size_t size = (size_t) *size_in;
  return zmq_msg_init_data (*msg, *data, size, &ffn, NULL);
}


int f77_zmq_msg_send_ (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return zmq_msg_send (*msg, *socket, *flags);
}


int f77_zmq_msg_recv_ (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return zmq_msg_recv (*msg, *socket, *flags);
}

 
void* f77_zmq_msg_data_ (zmq_msg_t* *msg)
{
  return zmq_msg_data(*msg);
}


int f77_zmq_msg_size_ (zmq_msg_t* *msg)
{
  const size_t rc = zmq_msg_size (*msg);
  return (int) rc;
}


int f77_zmq_msg_copy_from_data_ (zmq_msg_t* *msg, void* buffer, int dummy)
{
  const size_t sze = zmq_msg_size (*msg);
  void* data = zmq_msg_data (*msg);
  memcpy(buffer,data,sze*sizeof(char));
  return (int) sze;
}

int f77_zmq_msg_copy_to_data_ (zmq_msg_t* *msg, void* buffer, int* size_in, int dummy)
{
  const size_t size = (size_t) *size_in;
  void* data = zmq_msg_data (*msg);
  memcpy(data,buffer,size*sizeof(char));
  return 0;
}

int f77_zmq_msg_more_ (zmq_msg_t* *message)
{
  return zmq_msg_more (*message);
}


int f77_zmq_msg_get_ (zmq_msg_t* *message, int *property)
{
  return zmq_msg_get (*message, *property);
}


int f77_zmq_msg_set_ (zmq_msg_t* *message, int *property, int *value)
{
  return zmq_msg_set (*message, *property, *value);
}


int f77_zmq_msg_copy_ (zmq_msg_t* *dest, zmq_msg_t* *src)
{
  return zmq_msg_copy (*dest, *src);
}


int f77_zmq_msg_move_ (zmq_msg_t* *dest, zmq_msg_t* *src)
{
  return zmq_msg_move (*dest, *src);
}


/* Polling *
 * ======= */

int f77_zmq_poll_ (zmq_pollitem_t* *items, int *nitems, int *timeout)
{
  return zmq_poll (*items, *nitems, (long) *timeout);
}


void* f77_zmq_pollitem_new_ (int* nitems)
{
  zmq_pollitem_t *result = malloc (*nitems * sizeof(*result));
  return (void*) result;
}


int f77_zmq_pollitem_destroy_ (zmq_pollitem_t* *item)
{
  if (item != NULL)
  {
    free(*item);
  }
  return 0;
}

int f77_zmq_pollitem_set_socket_ (zmq_pollitem_t* *pollitem, int* i, void* *socket)
{
  (*pollitem)[(*i)-1].socket = *socket;
  return 0;
}

int f77_zmq_pollitem_set_events_ (zmq_pollitem_t* *pollitem, int* i, int* events)
{
  (*pollitem)[(*i)-1].events = (short) *events;
  return 0;
}

int f77_zmq_pollitem_revents_ (zmq_pollitem_t* *pollitem, int* i)
{
  return (int) (*pollitem)[(*i)-1].revents;
}

int f77_zmq_proxy_ (void* *frontend, void* *backend, void* *capture)
{
  return zmq_proxy(*frontend, *backend, *capture);
}



/* Pthreads bindings *
 * ================= */

#include <pthread.h>

int pthread_create_ (void* *newthread, void* subroutine (void *))
{
  int rc;
  *newthread = malloc (sizeof(pthread_t));
  rc = pthread_create( (pthread_t*) *newthread, NULL, subroutine, NULL);
  return rc;
}

int pthread_join_ (void* *thread)
{
  int rc;
  pthread_t* thread_pointer = (pthread_t*) *thread;
  rc = pthread_join( *thread_pointer, NULL );
  free(thread_pointer);
  *thread = NULL;
  return rc;
}


int pthread_detach_ (void* *thread)
{
  int rc;
  pthread_t* thread_pointer = (pthread_t*) *thread;
  rc = pthread_detach( *thread_pointer );
  free(thread_pointer);
  *thread = NULL;
  return rc;
}



