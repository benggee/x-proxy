CC=gcc
CFLAGS=

OBJECTS=main.o svc.o tcpserver.o log.o xtime.o proxy.o route.o tcpclient.o

.PHONY: clean


xproxy: $(OBJECTS) 
	$(CC) -o xproxy $(OBJECTS)

%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf xproxy *.o
