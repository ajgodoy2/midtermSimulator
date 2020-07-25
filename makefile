all: schedgen schedsim schedstats

schedgen: schedgen.o
	gcc -o schedgen schedgen.o

schedgen.o: schedgen.c
	gcc -c schedgen.c
     
schedsim: schedsim.o libscheduler.a
	gcc -o schedsim schedsim.o -L. -lscheduler

schedsim.o: schedsim.c 
	gcc -c schedsim.c

schedstats: schedstats.o libscheduler.a
	gcc -o schedstats schedstats.o -L. -lscheduler

schedstats.o: schedstats.c
	gcc -c schedstats.c

libscheduler.o: libscheduler.c
	gcc -c libscheduler.c

libscheduler.a: libscheduler.o
	ar rcs libscheduler.a libscheduler.o

clean:
	rm schedgen schedgen.o schedsim schedsim.o schedstats.o schedstats libscheduler.a libscheduler.o
