#gcc -E hello.c -o hello.i
#gcc -S hello.i -o hello.s
#gcc -c hello.s -o hello.o
#ld -static /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/7/crtbeginT.o -L/usr/lib/gcc/x86_64-linux-gnu/7 hello.o -start-group -lgcc -lgcc_eh -lc -end-group /usr/lib/gcc/x86_64-linux-gnu/7/crtend.o /usr/lib/x86_64-linux-gnu/crtn.o


CC = gcc
LIB_PATH = /usr/lib/x86_64-linux-gnu/
LIB_GCC_PATH = /usr/lib/gcc/x86_64-linux-gnu/7/

all:
	$(CC) -E hello.c -o hello.i
	$(CC) -S hello.i -o hello.s
	$(CC) -c hello.s -o hello.o
	ld -static $(LIB_PATH)crt1.o $(LIB_PATH)crti.o $(LIB_GCC_PATH)crtbeginT.o -L$(LIB_GCC_PATH) hello.o -start-group -lgcc -lgcc_eh -lc -end-group $(LIB_GCC_PATH)crtend.o $(LIB_PATH)crtn.o


clean:
	rm  -rf hello.i hello.s hello.o a.out
