      program server
        implicit none
        include 'f77_zmq.h'
        integer(ZMQ_PTR)  ::    context
        integer(ZMQ_PTR)  ::    python
        character*(64)    ::    address
        character(len=:), allocatable :: buffer
        integer           ::     rc, i
        double precision  :: data_send(10)
        double precision  :: data_recv(10)
       
        address = 'tcp://localhost:5555'
       
        context  = f77_zmq_ctx_new()
        python   = f77_zmq_socket(context, ZMQ_REQ)
        rc       = f77_zmq_connect(python,address)
       
        ! Data to send to the Python server
        do i=1,size(data_send)
          data_send(i) = dble(i)
        enddo
       
       print *,  'send'
        ! Send the data to the Python
        rc = f77_zmq_send (python, data_send, 8*size(data_send), 0)
       print *,  'rc'

        ! The Python sends back data_send + 1.d0
        rc = f77_zmq_recv (python, data_recv, 8*size(data_recv), 0)

        do i=1,size(data_recv)
          print *,  i, data_recv(i)
        enddo

        rc = f77_zmq_close(python)
        rc = f77_zmq_ctx_destroy(context)
      end

