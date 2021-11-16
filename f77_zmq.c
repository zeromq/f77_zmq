  /*
    F77_FUNC(f77_zm, F77_ZM)  : Fortran 77 bindings for the ZeroMQ library
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

#include "config.h"
#include "zmq.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>


/* Guidelines
 * ==========
 *
 * + Fortran-callable function names should start with f77_zmq_ and should be built with the F77_FUNC macro.
 * + A space should be present between the the name of the function and the '(' character for the
 *   python script to work properly.
 * + void* return types will be translated to INTEGER(ZMQ_PTR)
 * + int   return types will be translated to INTEGER
 *
 */

/* Helper functions *
  ================ */

int F77_FUNC(f77_zmq_errno, F77_ZMQ_ERRNO)  (void)
{
  return zmq_errno ();
}

char* F77_FUNC(f77_zmq_strerror, F77_ZMQ_STRERROR)  (int *errnum)
{
  return (char*) zmq_strerror (*errnum);
}

int F77_FUNC(f77_zmq_version, F77_ZMQ_VERSION)  (int *major, int *minor, int *patch)
{
  zmq_version (major, minor, patch);
  return 0;
}

int F77_FUNC(f77_zmq_microsleep, F77_ZMQ_MICROSLEEP)  (int* microsecs)
{
  struct timespec ts, ts2;
  ts.tv_sec  = 0;
  ts.tv_nsec = 1000L * ( (long) (*microsecs));
  return nanosleep (&ts, &ts2);
}

/* Context *
 * ======= */

void* F77_FUNC(f77_zmq_ctx_new, F77_ZMQ_CTX_NEW)  ()
{
    return zmq_ctx_new ();
}

int F77_FUNC(f77_zmq_ctx_term, F77_ZMQ_CTX_TERM)  (void* *context)
{
    return zmq_ctx_term (*context);
}

int F77_FUNC(f77_zmq_ctx_shutdown, F77_ZMQ_CTX_SHUTDOWN)  (void* *context)
{
    return zmq_ctx_shutdown (*context);
}

int F77_FUNC(f77_zmq_ctx_get, F77_ZMQ_CTX_GET)  (void* *context, int* option_name)
{
  return zmq_ctx_get (*context, *option_name );
}

int F77_FUNC(f77_zmq_ctx_set, F77_ZMQ_CTX_SET)  (void* *context, int* option_name, int* option_value)
{
  return zmq_ctx_set (*context, *option_name, *option_value);
}

/* Old (legacy) API */
int F77_FUNC(f77_zmq_term, F77_ZMQ_TERM)  (void* *context)
{
    return zmq_term (*context);
}

int F77_FUNC(f77_zmq_ctx_destroy, F77_ZMQ_CTX_DESTROY)  (void* *context)
{
    return zmq_ctx_destroy (*context);
}


/* Sockets *
 * ======= */

void* F77_FUNC(f77_zmq_socket, F77_ZMQ_SOCKET)  (void* *context, int* type)
{
    return zmq_socket (*context, *type);
}

int F77_FUNC(f77_zmq_close, F77_ZMQ_CLOSE)  (void* *socket)
{
    return zmq_close(*socket);
}

int F77_FUNC(f77_zmq_bind, F77_ZMQ_BIND)  (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
    if (address_in[i] == ' ')
    {
      address[i] = 0;
      i = address_len;
    }
  }
  address[address_len] = 0;
  rc = zmq_bind (*socket, address);
  free(address);
  return rc;
}


int F77_FUNC(f77_zmq_unbind, F77_ZMQ_UNBIND)  (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
    if (address_in[i] == ' ')
    {
      address[i] = 0;
      i = address_len;
    }
  }
  address[address_len] = 0;
  rc = zmq_unbind (*socket, address);
  free(address);
  return rc;
}



int F77_FUNC(f77_zmq_connect, F77_ZMQ_CONNECT)  (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
    if (address_in[i] == ' ')
    {
      address[i] = 0;
      i = address_len;
    }
  }
  address[address_len] = 0;
  rc = zmq_connect (*socket, address);
  free(address);
  return rc;
}


int F77_FUNC(f77_zmq_disconnect, F77_ZMQ_DISCONNECT)  (void* *socket, char* address_in, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
    if (address_in[i] == ' ')
    {
      address[i] = 0;
      i = address_len;
    }
  }
  address[address_len] = 0;
  rc = zmq_disconnect (*socket, address);
  free(address);
  return rc;
}

int F77_FUNC(f77_zmq_setsockopt, F77_ZMQ_SETSOCKOPT)  (void* *socket, int* option_name, void* option_value, int* option_len, int dummy)
{
  int result;
  void * value = malloc(*option_len);
  memcpy(value, option_value, (size_t) *option_len);
  result = zmq_setsockopt (*socket, *option_name, value, (size_t) *option_len);
  free(value);
  return result;
}

int F77_FUNC(f77_zmq_getsockopt, F77_ZMQ_GETSOCKOPT)  (void* *socket, int* option_name, void *option_value, int *option_len, int dummy)
{
  size_t option_len_st = (size_t) *option_len;
  return zmq_getsockopt (*socket, *option_name, option_value, &option_len_st);
  *option_len = option_len_st;
}

int F77_FUNC(f77_zmq_socket_monitor, F77_ZMQ_SOCKET_MONITOR)  (void* *socket, char* address_in, int* events, int address_len)
{
  char* address = malloc((address_len+1) * sizeof(*address) );
  int rc;
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
    if (address_in[i] == ' ')
    {
      address[i] = 0;
      i = address_len;
    }
  }
  address[address_len] = 0;
  rc = zmq_socket_monitor(*socket,address,*events);
  free(address);
  return rc;
}

/* Send/Recv *
 * ========= */

int F77_FUNC(f77_zmq_send, F77_ZMQ_SEND)  (void* *socket, void* message, int* message_len, int* flags, int dummy)
{
  return (int) zmq_send (*socket, message, (size_t) *message_len, *flags);
}

int F77_FUNC(f77_zmq_send_const, F77_ZMQ_SEND_CONST)  (void* *socket, void* message, int* message_len, int* flags, int dummy)
{
  return (int) zmq_send_const (*socket, message, (size_t) *message_len, *flags);
}

int F77_FUNC(f77_zmq_recv, F77_ZMQ_RECV)  (void* *socket, void* message, int* message_len, int* flags, int dummy)
{
  return (int) zmq_recv (*socket, message, (size_t) *message_len, *flags);
}


long F77_FUNC(f77_zmq_send8, F77_ZMQ_SEND8)  (void* *socket, void* message, long* message_len, int* flags, int dummy)
{
  return (long) zmq_send (*socket, message, (size_t) *message_len, *flags);
}

long F77_FUNC(f77_zmq_send_const8, F77_ZMQ_SEND_CONST8)  (void* *socket, void* message, long* message_len, int* flags, int dummy)
{
  return (long) zmq_send_const (*socket, message, (size_t) *message_len, *flags);
}

long F77_FUNC(f77_zmq_recv8, F77_ZMQ_RECV8)  (void* *socket, void* message, long* message_len, int* flags, int dummy)
{
  return (long) zmq_recv (*socket, message, (size_t) *message_len, *flags);
}



/* Messages *
 * ======== */

void* F77_FUNC(f77_zmq_msg_new, F77_ZMQ_MSG_NEW)  ()
{
  return malloc (sizeof(zmq_msg_t));
}

int F77_FUNC(f77_zmq_msg_destroy, F77_ZMQ_MSG_DESTROY)  (zmq_msg_t* *msg)
{
  if (*msg != NULL)
  {
    free(*msg);
  }
  return 0;
}

void* F77_FUNC(f77_zmq_msg_data_new, F77_ZMQ_MSG_DATA_NEW)  (int* size_in, void* buffer, int* size_buffer, int dummy)
{
  void* data = malloc(*size_in * sizeof(char));
  if (*size_buffer > 0)
    memcpy(data,buffer,(size_t) *size_buffer);
  return data;
}

int F77_FUNC(f77_zmq_msg_destroy_data, F77_ZMQ_MSG_DESTROY_DATA)  (void* *data)
{
  if (*data != NULL)
  {
    free(*data);
    data = NULL;
  }
  return 0;
}


int F77_FUNC(f77_zmq_msg_init, F77_ZMQ_MSG_INIT)  (zmq_msg_t* *msg)
{
  return zmq_msg_init (*msg);
}


int F77_FUNC(f77_zmq_msg_close, F77_ZMQ_MSG_CLOSE)  (zmq_msg_t* *msg)
{
  return zmq_msg_close (*msg);
}


int F77_FUNC(f77_zmq_msg_init_size, F77_ZMQ_MSG_INIT_SIZE)  (zmq_msg_t* *msg, int* size_in)
{
  size_t size = (size_t) *size_in;
  return zmq_msg_init_size (*msg, size);
}


void ffn(void* data, void* hint)
{
     free(data);
}

int F77_FUNC(f77_zmq_msg_init_data, F77_ZMQ_MSG_INIT_DATA)  (zmq_msg_t* *msg, void* *data, int* size_in)
{
  size_t size = (size_t) *size_in;
  return zmq_msg_init_data (*msg, *data, size, &ffn, NULL);
}


int F77_FUNC(f77_zmq_msg_send, F77_ZMQ_MSG_SEND)  (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return (int) zmq_msg_send (*msg, *socket, *flags);
}


long F77_FUNC(f77_zmq_msg_send8, F77_ZMQ_MSG_SEND8)  (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return (long) zmq_msg_send (*msg, *socket, *flags);
}


int F77_FUNC(f77_zmq_msg_recv, F77_ZMQ_MSG_RECV)  (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return (int) zmq_msg_recv (*msg, *socket, *flags);
}

long F77_FUNC(f77_zmq_msg_recv8, F77_ZMQ_MSG_RECV8)  (zmq_msg_t* *msg, void* *socket, int* flags)
{
   return (long) zmq_msg_recv (*msg, *socket, *flags);
}

 
void* F77_FUNC(f77_zmq_msg_data, F77_ZMQ_MSG_DATA)  (zmq_msg_t* *msg)
{
  return zmq_msg_data(*msg);
}


int F77_FUNC(f77_zmq_msg_size, F77_ZMQ_MSG_SIZE)  (zmq_msg_t* *msg)
{
  const size_t rc = zmq_msg_size (*msg);
  return (int) rc;
}

long F77_FUNC(f77_zmq_msg_size8, F77_ZMQ_MSG_SIZE8)  (zmq_msg_t* *msg)
{
  const size_t rc = zmq_msg_size (*msg);
  return (long) rc;
}


int F77_FUNC(f77_zmq_msg_copy_from_data, F77_ZMQ_MSG_COPY_FROM_DATA)  (zmq_msg_t* *msg, void* buffer, int dummy)
{
  const size_t sze = zmq_msg_size (*msg);
  void* data = zmq_msg_data (*msg);
  memcpy(buffer,data,sze*sizeof(char));
  return (int) sze;
}

int F77_FUNC(f77_zmq_msg_copy_to_data, F77_ZMQ_MSG_COPY_TO_DATA)  (zmq_msg_t* *msg, void* buffer, int* size_in, int dummy)
{
  const size_t size = (size_t) *size_in;
  void* data = zmq_msg_data (*msg);
  memcpy(data,buffer,size*sizeof(char));
  return 0;
}

int F77_FUNC(f77_zmq_msg_copy_to_data8, F77_ZMQ_MSG_COPY_TO_DATA8)  (zmq_msg_t* *msg, void* buffer, long* size_in, int dummy)
{
  const size_t size = (size_t) *size_in;
  void* data = zmq_msg_data (*msg);
  memcpy(data,buffer,size*sizeof(char));
  return 0;
}

int F77_FUNC(f77_zmq_msg_more, F77_ZMQ_MSG_MORE)  (zmq_msg_t* *message)
{
  return zmq_msg_more (*message);
}


int F77_FUNC(f77_zmq_msg_get, F77_ZMQ_MSG_GET)  (zmq_msg_t* *message, int *property)
{
  return zmq_msg_get (*message, *property);
}


char* F77_FUNC(f77_zmq_msg_gets, F77_ZMQ_MSG_GETS)  (zmq_msg_t* *message, char* property_in, int property_len)
{
  const char* rc;
  char* property = malloc((property_len+1) * sizeof(*property) );
  int i;
  for (i=0 ; i<property_len ; i++)
  {
    property[i] = property_in[i];
    if (property_in[i] == ' ')
    {
      property[i] = 0;
      i = property_len;
    }
  }
  property[property_len] = 0;
  rc = zmq_msg_gets (*message, property);
  free(property);
  return (char*) rc;
}


int F77_FUNC(f77_zmq_msg_set, F77_ZMQ_MSG_SET)  (zmq_msg_t* *message, int *property, int *value)
{
  return zmq_msg_set (*message, *property, *value);
}


int F77_FUNC(f77_zmq_msg_copy, F77_ZMQ_MSG_COPY)  (zmq_msg_t* *dest, zmq_msg_t* *src)
{
  return zmq_msg_copy (*dest, *src);
}


int F77_FUNC(f77_zmq_msg_move, F77_ZMQ_MSG_MOVE)  (zmq_msg_t* *dest, zmq_msg_t* *src)
{
  return zmq_msg_move (*dest, *src);
}




/* Polling *
 * ======= */

int F77_FUNC(f77_zmq_poll, F77_ZMQ_POLL)  (zmq_pollitem_t* *items, int *nitems, int *timeout)
{
  return zmq_poll (*items, *nitems, (long) *timeout);
}


void* F77_FUNC(f77_zmq_pollitem_new, F77_ZMQ_POLLITEM_NEW)  (int* nitems)
{
  zmq_pollitem_t *result = malloc (*nitems * sizeof(*result));
  return (void*) result;
}


int F77_FUNC(f77_zmq_pollitem_destroy, F77_ZMQ_POLLITEM_DESTROY)  (zmq_pollitem_t* *item)
{
  if (item != NULL)
  {
    free(*item);
  }
  return 0;
}

int F77_FUNC(f77_zmq_pollitem_set_socket, F77_ZMQ_POLLITEM_SET_SOCKET)  (zmq_pollitem_t* *pollitem, int* i, void* *socket)
{
  (*pollitem)[(*i)-1].socket = *socket;
  return 0;
}

int F77_FUNC(f77_zmq_pollitem_set_events, F77_ZMQ_POLLITEM_SET_EVENTS)  (zmq_pollitem_t* *pollitem, int* i, int* events)
{
  (*pollitem)[(*i)-1].events = (short) *events;
  return 0;
}

int F77_FUNC(f77_zmq_pollitem_revents, F77_ZMQ_POLLITEM_REVENTS)  (zmq_pollitem_t* *pollitem, int* i)
{
  return (int) (*pollitem)[(*i)-1].revents;
}

int F77_FUNC(f77_zmq_proxy, F77_ZMQ_PROXY)  (void* *frontend, void* *backend, void* *capture)
{
  return zmq_proxy(*frontend, *backend, *capture);
}

int F77_FUNC(f77_zmq_proxy_steerable, F77_ZMQ_PROXY_STEERABLE)  (void* *frontend, void* *backend, void* *capture,
    void* *control)
{
  return zmq_proxy_steerable(*frontend, *backend, *capture, *control);
}




/* Pthreads bindings *
 * ================= */

#include <pthread.h>

int F77_FUNC(pthread_create, PTHREAD_CREATE)  (void* *newthread, void* subroutine (void *))
{
  int rc;
  *newthread = malloc (sizeof(pthread_t));
  rc = pthread_create( (pthread_t*) *newthread, NULL, subroutine, NULL);
  return rc;
}

int F77_FUNC(pthread_create_arg, PTHREAD_CREATE_ARG)  (void* *newthread, void* subroutine (void *), void* arg)
{
  int rc;
  *newthread = malloc (sizeof(pthread_t));
  rc = pthread_create( (pthread_t*) *newthread, NULL, subroutine, arg);
  return rc;
}

int F77_FUNC(pthread_join, PTHREAD_JOIN)  (void* *thread)
{
  int rc;
  pthread_t* thread_pointer = (pthread_t*) *thread;
  rc = pthread_join( *thread_pointer, NULL );
  free(thread_pointer);
  *thread = NULL;
  return rc;
}


int F77_FUNC(pthread_detach, PTHREAD_DETACH)  (void* *thread)
{
  int rc;
  pthread_t* thread_pointer = (pthread_t*) *thread;
  rc = pthread_detach( *thread_pointer );
  free(thread_pointer);
  *thread = NULL;
  return rc;
}


