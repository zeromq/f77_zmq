      program server
        implicit none
        include 'f77_zmq.h'
        integer(ZMQ_PTR)        context
        integer(ZMQ_PTR)        responder
        integer(ZMQ_PTR)        request, reply
        character*(64)          address
        character*(20)          buffer
        integer                 rc
       
       
        address = 'tcp://*:5555'
       
        context   = f77_zmq_ctx_new()
        responder = f77_zmq_socket(context, ZMQ_REP)
        rc        = f77_zmq_bind(responder,address)
       
        do
          rc = f77_zmq_msg_init(request)
          if (rc /= 0) stop 'f77_zmq_msg_init failed'

          rc = f77_zmq_msg_recv(request, responder, 0)

          rc = f77_zmq_msg_copy_from_data (request, buffer)

          print *,  'Received :', buffer(1:rc)

          rc = f77_zmq_msg_close(request)
          if (rc /= 0) stop 'f77_zmq_msg_close failed'

          rc = f77_zmq_msg_init_size(reply,5)
          if (rc /= 0) stop 'f77_zmq_msg_init_size failed'

          rc = f77_zmq_msg_copy_to_data (request, buffer, 5)
          if (rc /= 0) stop 'f77_zmq_msg_data failed'
          buffer = 'World'

          rc = f77_zmq_msg_send(reply, responder, 0)

          rc = f77_zmq_msg_close(reply)
          if (rc /= 0) stop 'f77_zmq_msg_close failed'

        enddo

      end

