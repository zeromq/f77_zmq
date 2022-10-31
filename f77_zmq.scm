(define-module (gnu packages hello)
  #:use-module (guix packages)
  #:use-module (guix download)
  #:use-module (guix build-system gnu)
  #:use-module (guix licenses)
  #:use-module (gnu packages gcc)
  #:use-module (gnu packages networking)
  #:use-module (gnu packages python))

(define-public f77_zmq
  (package
   (name "f77_zmq")
   (version "4.3.3")
   (source (origin
            (method url-fetch)
            (uri (string-append
                  "https://github.com/zeromq/f77_zmq/releases/download/v"
                  version
                  "4.3.3/f77-zmq-"
                  version
                  ".tar.gz"))
            (sha256
             (base32
              "0k70riil3fczymp17184rzfvzfvy0k8a6s9yfwyrrh2qyrz797hf"))))
   (build-system gnu-build-system)
   (arguments '(#:configure-flags '("--enable-silent-rules")))
   (inputs `(
             ("gcc", gcc)
             ("gfortran", gfortran)
             ("python", python)
             ("zeromq", zeromq)
             ))
   (synopsis "ZeroMQ Fortran77 binding")
   (description "Fortran77 binding for the ZeroMQ lightweight messaging library.")
   (home-page "https://github.com/zeromq/f77_zmq")
   (license lgpl2.1+)))

f77_zmq
