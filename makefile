CC=cc
CCFLAGS=-Wall -Wextra -O
sock_lib.o:sock_lib.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
search.o:search.c
	$(CC) $(CCFLAGS) -g -c $< -o $@	
stack.o:stack.c
	$(CC) $(CCFLAGS) -g -c $< -o $@	
main:main.c sock_lib.o
	$(CC) $(CCFLAGS) -g $^ -o $@
iterative_server:iterative_server.c sock_lib.o search.o stack.o
	$(CC) $(CCFLAGS) -g $^ -o $@
