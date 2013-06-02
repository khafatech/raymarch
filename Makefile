

CC = g++

CFLAGS = -Wall -O3 #-pg -g

LDFLAGS = 

HANDIN_FILES = 

TAR = raytrace.tgz


all: raytrace

raytrace:	raytrace.o image.o util.o
		$(CC) $(CFLAGS) $^ -o $@ 

raytrace_debug:	raytrace_debug.o image.o util.o
		$(CC) $^ -o $@ $(CFLAGS)

terrain:	terrain.o image.o util.o
		$(CC) $^ -o $@ $(CFLAGS)

test_intersect:	test_intersect.o util.o
		$(CC) $(CFLAGS) $^ -o $@ 


%.o: %.cpp $(wildcard %.h)
		$(CC) $(CFLAGS) $< -c


handin:
		tar -czf ../$(TAR) ../raytrace
		scp ../$(TAR) unix3:~/Desktop
		ssh unix3 "handin zwood csc473p4 Desktop/$(TAR)"

upload:
		tar -czf ../$(TAR) ../raytrace
		scp ../$(TAR) unix3:~/Desktop

