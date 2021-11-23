all: lab-3-server.exe lab-3-client.exe
lab-3-server.exe: lab-3-server.o function.o
	gcc lab-3-server.o function.o -o lab-3-server.exe
functoin.o: function.c
	gcc -c finction.c
lab-3-server.o: lab-3-server.c
	gcc -c lab-3-server.c
lab-3-client.exe:
	gcc lab-3-client.o -o lab-3-client.exe
lab-3-client.o: lab-3-client.c 
	gcc -c lab-3-client.c
clean:
	rm -rf *.o
