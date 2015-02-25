all: hello
hello: client1 server1
client1:client1.c
		gcc  client1.c -o client
server1: server1.c
		gcc  server1.c -o server
run: ./server 
	./server  4547
run1: ./client
	./client localhost 4547
clean: 
	rm -f  client server

