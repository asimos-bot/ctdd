CC := gcc

object_files = $(addsuffix .o, $(basename $(wildcard list*.c)))

.PHONY: test clean done runner

test: CFLAGS := -fPIC -g -O0
test: runner
	@valgrind -q --leak-check=full --show-leak-kinds=all ./runner

runner: list.o runner.o
	@$(CC) $^ -o runner

done: CFLAGS := -O3 -fPIC
done: list.o
	$(CC) -O3 -fPIC -shared list.o -o liblist.so

clean:
	rm runner *.o *.so

list_final.o: $(object_files)
	ld -r $^ -o $@

$(object_files): %.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

runner.o: runner.c
	$(CC) runner.c $(CFLAGS) -c -o runner.o
