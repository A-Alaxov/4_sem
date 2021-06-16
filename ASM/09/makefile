.PHONY : clean

CC := gcc

CFLAGS := -std=gnu11 -w -masm=intel #-ggdb

all : app.exe app_no_gen.exe

app_no_gen.exe : test_01.o test_02.o test_03.o main_0.o
	$(CC) -o $@ $^

app.exe : test_11.o test_12.o test_13.o main_1.o
	$(CC) -o $@ $^
	

test_01.o : test_01.c
	$(CC) $(CFLAGS) -DNO_i387 -mno-80387 -c $< -o $@

test_02.o : test_02.c
	$(CC) $(CFLAGS) -DNO_i387 -mno-80387 -c $< -o $@

test_03.o : test_03.c
	$(CC) $(CFLAGS) -DNO_i387 -mno-80387 -c $< -o $@

main_0.o : main.c
	$(CC) $(CFLAGS) -DNO_i387 -mno-80387 -c $< -o $@


test_11.o : test_01.c
	$(CC) $(CFLAGS) $(SSEFLAGS) -m80387 -c $< -o $@

test_12.o : test_02.c
	$(CC) $(CFLAGS) $(SSEFLAGS) -m80387 -c $< -o $@

test_13.o : test_03.c
	$(CC) $(CFLAGS) $(SSEFLAGS) -m80387 -c $< -o $@

main_1.o : main.c
	$(CC) $(CFLAGS) $(SSEFLAGS) -m80387 -c $< -o $@


clean :
	rm *.exe *.o