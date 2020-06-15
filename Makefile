CC=gcc

runner: runner.o test.o
	strip -N main test.o -o _test.o
	$(CC) runner.o _test.o -o $@ 

test.o: test.c
	$(CC) test.c -c -o test.o
runner.o: runner.c
	$(CC) runner.c -c -o runner.o
clean:
	rm _test.o test.o runner.o runner
