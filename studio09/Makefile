.PHONY: all clean

all: busyloop_rt busyloop_rtfork

busyloop_rt: busyloop_rt.c
	gcc busyloop_rt.c -O0 -o busyloop_rt 

busyloop_rtfork: busyloop_rtfork.c
	gcc busyloop_rtfork.c -O0 -o busyloop_rtfork

clean:
	rm -rf busyloop_rt busyloop_rtfork
