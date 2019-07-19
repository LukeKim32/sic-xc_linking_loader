sicxe_linking_loader.out : sicxe_linking_loader.o
	gcc -Wall -o sicxe_linking_loader.out sicxe_linking_loader.o

sicxe_linking_loader.o : sicxe_linking_loader.c
	gcc -Wall -c -o sicxe_linking_loader.o sicxe_linking_loader.c

clean :
	rm *.o sicxe_linking_loader.out
 
