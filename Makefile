

CC = g++

CFLAGS = -Wall

LDFLAGS = 

HANDIN_FILES = 

TAR = raytrace.tgz


all: raytrace

raytrace:	raytrace.o image.o util.o
		$(CC) $(CFLAGS) $^ -o $@ 

test_intersect:	test_intersect.o util.o
		$(CC) $(CFLAGS) $^ -o $@ 


%.o: %.c $(wildcard %.h)
		$(CC) $(CFLAGS) $< -c


handin:
		tar -czf $(TAR) ../raytrace
		scp $(TAR) unix3:~/Desktop
		ssh unix3 "handin zwood csc473p1 Desktop/$(TAR)"

upload:
		tar -czf $(TAR) ../raytrace
		scp $(TAR) unix3:~/Desktop

