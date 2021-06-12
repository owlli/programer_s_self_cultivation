#gcc -fPIC -shared -o Lib.so Lib.c
#gcc -o Program1 Program1.c ./Lib.so
#gcc -o Program2 Program2.c ./Lib.so
#gcc -o PrintStack64bit PrintStack64bit.c
#gcc -o PrintStack32bit PrintStack32bit.c
#gcc -fPIC -shared a1.c -o a1.so
#gcc -fPIC -shared a2.c -o a2.so
#gcc -fPIC -shared b1.c a1.so -o b1.so
#gcc -fPIC -shared b2.c a2.so -o b2.so
#gcc main.c b1.so b2.so -o main -Xlinker -rpath ./

CC = gcc
DSO_FLAGS = -fPIC -shared

all: Program1 Program2 PrintStack64bit PrintStack32bit main RunSoSimple RunSo

Program1: Program1.o Lib.so
	$(CC) -o $@ $^

Program1.o: Program1.c

Program2: Program2.o Lib.so
	$(CC) -o $@ $^

Program2.o: Program2.c

Lib.so: Lib.c
	$(CC) $(DSO_FLAGS) -o $@ $^

PrintStack64bit: PrintStack64bit.o
	$(CC) -o $@ $^

#PrintStack64bit.o: PrintStack64bit.c

PrintStack32bit: PrintStack32bit.o
	$(CC) -o $@ $^ -m32

PrintStack32bit.o: PrintStack32bit.c
	$(CC) -c $^ -m32

main: main.c b1.so b2.so
	$(CC) $^ -o $@ -Xlinker -rpath ./

b1.so: b1.c a1.so
	$(CC) $(DSO_FLAGS) $^ -o $@

b2.so: b2.c a2.so
	$(CC) $(DSO_FLAGS) $^ -o $@

a1.so: a1.c
	$(CC) $(DSO_FLAGS) $^ -o $@

a2.so: a2.c
	$(CC) $(DSO_FLAGS) $^ -o $@

RunSoSimple: RunSoSimple.c
	$(CC) -o $@ $^ -ldl

RunSo: RunSo.c
	$(CC) -o $@ $^ -ldl -m32

%.o: %.c
	$(CC) -c $<

clean:
	rm -rf *.so *.o Program1 Program2 PrintStack64bit PrintStack32bit main RunSoSimple RunSo
