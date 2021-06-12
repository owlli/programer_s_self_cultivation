#gcc -fno-stack-protector -c a.c b.c
#ld a.o b.o -e main -o ab
#gcc -c -fno-builtin TinyHelloWorld.c
#ld -static -e nomain -o TinyHelloWorld TinyHelloWorld.o

CC = gcc

A_B_CFLAGS = -fno-stack-protector

all: ab TinyHelloWorld target

ab: a.o b.o
	ld $^ -e main -o $@

a.o: a.c
	$(CC) -c $(A_B_CFLAGS) $< -o $@

b.o: b.c
	$(CC) -c $(A_B_CFLAGS) $< -o $@

TinyHelloWorld: TinyHelloWorld.o
	ld -static -T TinyHelloWorld.lds -m elf_i386 -e nomain -o $@ $<

TinyHelloWorld.o: TinyHelloWorld.c
	$(CC) -c -fno-builtin -m32 $<

target: target.c
	gcc -o $@ $< -lbfd

clean:
	rm -rf a.o b.o ab TinyHelloWorld.o TinyHelloWorld target
