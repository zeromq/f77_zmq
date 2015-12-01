      module ctx
        include 'f77_zmq.h'
        integer(ZMQ_PTR)      context
      end module

      subroutine task_worker
!       Task worker
!       Connects PULL socket to inproc://5557
!       Collects workloads from ventilator via that socket
!       Connects PUSH socket to inproc://5558
!       Sends results to sink via that socket
        use ctx
        implicit none

        integer               rc
        integer               msecs
        character*(20)        string

        integer(ZMQ_PTR)      sender, receiver, sink
        ! Socket to receive messages on
        receiver = f77_zmq_socket(context,ZMQ_PULL)
        rc = f77_zmq_connect (receiver, "inproc://5557")
        if (rc /= 0) stop '1st Connect failed'
       
        ! Socket to send messages to
        sender = f77_zmq_socket (context, ZMQ_PUSH);
        rc = f77_zmq_connect (sender, "inproc://5558");
        if (rc /= 0) stop '2nd Connect failed'

        msecs = 1
        do while (msecs >= 0)
            rc = f77_zmq_recv (receiver, string, 20, 0)
!            print '(A)', string(1:rc)
            read(string(1:rc),*) msecs
            call milli_sleep(msecs)
            rc = f77_zmq_send (sender, "", 0, 0) ! Send results to sink
        enddo
        rc = f77_zmq_close (receiver);
        rc = f77_zmq_close (sender);
      end

      subroutine milli_sleep(ms)
        implicit none
        integer                 ms
        integer                 t(8), ms1, ms2
        call date_and_time(values=t)
        ms1=(t(5)*3600+t(6)*60+t(7))*1000+t(8)
        do ! check time:
          call date_and_time(values=t)
          ms2=(t(5)*3600+t(6)*60+t(7))*1000+t(8)
          if(ms2<ms1) then
            ms1 = ms1 - 24*3600*1000
          endif
          if(ms2-ms1>=ms)exit
        enddo

      end

      subroutine task_ventilator
!       Task ventilator
!       Binds PUSH socket to inproc://5557
!       Sends batch of tasks to workers via that socket
        use ctx
        implicit none

        integer(ZMQ_PTR)      sender, sink
        integer               rc
        integer               task_nbr
        integer               total_msec
        integer               workload
        double precision      r
        character*(10)        string

        sender  = f77_zmq_socket(context,ZMQ_PUSH)
        rc = f77_zmq_bind (sender, "inproc://5557")
        if (rc /= 0) stop 'Bind failed'

        ! Socket to send start of batch message on
        sink = f77_zmq_socket (context, ZMQ_PUSH)
        rc = f77_zmq_connect (sink, "inproc://5558")
        if (rc /= 0) stop 'Connect failed'

        call sleep(1)
        ! The first message is "0" and signals start of batch
        rc = f77_zmq_send (sink, '0', 1, 0);
        if (rc /= 1) stop 'Send failed'

        ! Send 100 tasks
        total_msec = 0     ! Total expected cost in msecs
        do task_nbr=1,100
            ! Random workload from 1 to 100msecs
            call random_number(r)
            workload = int(100.*r) + 1
            total_msec = total_msec + workload
            write(string,'(I8)') workload
!            print '(A)', string
            rc = f77_zmq_send(sender,string,len(trim(string)),0)
        enddo
        do task_nbr=1,4
          rc = f77_zmq_send(sender,'-1',2,0)
        enddo
        print *, 'Total expected cost: ',total_msec,' msec'
       
        rc = f77_zmq_close (sink)
        rc = f77_zmq_close (sender)
      end


      program main
        use ctx
        implicit none
        external :: task_worker, task_ventilator
        integer(ZMQ_PTR) :: thread(5)
        integer :: i, rc

        context  = f77_zmq_ctx_new()
        rc = pthread_create ( thread(5), task_ventilator )
        if (rc /= 0) then
          stop 'Failed to create task_ventilator thread'
        endif
        do i=1,4
          rc = pthread_create (thread(i), task_worker)
          if (rc /= 0) then
            stop 'Failed to create task_worker thread'
          endif
        enddo
!        rc = pthread_detach( thread(5) )
!        if (rc /= 0) then
!          stop 'Failed to detach thread 5'
!        endif
!        do i=1,4
        do i=1,5
          rc = pthread_join( thread(i) )
          if (rc /= 0) then
            stop 'Failed to join thread '
          endif
          print *,  'Joined ', i
        enddo
        rc = f77_zmq_ctx_destroy (context)
      end
