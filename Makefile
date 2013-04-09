

CC = g++

CFLAGS = -Wall

LDFLAGS = 

HANDIN_FILES = 




all: raytrace

raytrace:	raytrace.o
		$(CC) $(CFLAGS) $^ -o $@ 


%.o: %.c $(wildcard %.h)
		$(CC) $(CFLAGS) $< -c


handin:
		scp $(HANDIN_FILES) unix3:...
		ssh unix3 " pn-cs453 $(HANDIN_FILES)"


