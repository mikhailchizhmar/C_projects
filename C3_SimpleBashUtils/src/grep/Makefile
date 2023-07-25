
TARGET = my_grep

CC = gcc -Werror -Wextra -Wall

all:
	$(CC) -o $(TARGET) grep.c ../common/arrays.c ../common/misc.c ../common/queue.c -lpcre

clean:
	rm -rf *.o $(TARGET)

my_grep: all

rebuild: clean all