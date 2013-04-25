

CC = g++

CFLAGS = -g -Wall # -O3

LDFLAGS = 

HANDIN_FILES = 

TAR = raytrace.tgz


all: raytrace

raytrace:	raytrace.o image.o util.o
		$(CC) $^ -o $@ $(CFLAGS)

test_intersect:	test_intersect.o util.o
		$(CC) $(CFLAGS) $^ -o $@ 


%.o: %.c $(wildcard %.h)
		$(CC) $< -c $(CFLAGS)


handin:
		tar -czf $(TAR) ../raytrace
		scp $(TAR) unix3:~/Desktop
		ssh unix3 "handin zwood csc473p1 Desktop/$(TAR)"

upload:
		tar -czf $(TAR) ../raytrace
		scp $(TAR) unix3:~/Desktop

