#include "zmq.h"
#include "stdlib.h"

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
  char address[address_len+1];
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
  }
  address[address_len] = 0;
  return zmq_bind (*socket, address);
}

int f77_zmq_connect_ (void* *socket, char* address_in, int address_len)
{
  char address[address_len+1];
  int i;
  for (i=0 ; i<address_len ; i++)
  {
    address[i] = address_in[i];
  }
  address[address_len] = 0;
  return zmq_connect (*socket, address);
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

int f77_zmq_msg_init_ (zmq_msg_t* *msg)
{
  *msg = (zmq_msg_t*) malloc (sizeof(zmq_msg_t));
  return zmq_msg_init (*msg);
}


int f77_zmq_msg_close_ (zmq_msg_t* *msg)
{
  int rc = zmq_msg_close (*msg);
  if (rc == 0)
    free(*msg);
  return rc;
}


int f77_zmq_msg_init_size_ (zmq_msg_t* *msg, int* size_in)
{
  size_t size = (size_t) *size_in;
  return zmq_msg_init_size (*msg, size);
}


int f77_zmq_msg_init_data_ (zmq_msg_t* *msg, void *data, int* size_in, zmq_free_fn *ffn, void *hint)
{
  size_t size = (size_t) *size_in;
  *msg = (zmq_msg_t*) malloc (sizeof(zmq_msg_t));
  return zmq_msg_init_data (*msg, data, size, ffn, hint);
}


// int f77_zmq_msg_send_ (zmq_msg_t* *msg, void* *socket, int* flags)
// {
//   return zmq_msg_send (*msg, *socket, *flags);
// }
// 
// 
// int f77_zmq_msg_recv_ (zmq_msg_t* *msg, void* *socket, int* flags)
// {
//   return zmq_msg_recv (*msg, *socket, *flags);
// }
// 
// 
// int f77_zmq_msg_data_ (zmq_msg_t* *msg, void* data)
// {
//   data = zmq_msg_data(*msg);
//   return (data != NULL);
// }
// 

int f77_zmq_msg_size_ (zmq_msg_t* *msg)
{
  size_t rc = zmq_msg_size (*msg);
  return (int) rc;
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

int f77_zmq_poll_ (zmq_pollitem_t *items, int *nitems, long *timeout)
{
  return zmq_poll (items, *nitems, *timeout);
}




