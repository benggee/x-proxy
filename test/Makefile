CC=gcc
CFLAGS=
OBJECTS=test.o svc.o tcpserver.o log.o xtime.o proxy.o route.o tcpclient.o

.PHONY: clean

test: $(OBJECTS) 
	$(CC) -o test $(OBJECTS)

svc.o: svc.h tcpserver.h log.h
tcpserver.o: tcpserver.h
log.o: log.h xtime.h
proxy.o: tcpserver.h log.h route.h hh.h tcpclient.h
tcpclient.o: tcpclient.h svc.h
xtime.o: xtime.h
route.o: route.h svc.h

clean:
	rm -rf *.o
	rm -rf test
