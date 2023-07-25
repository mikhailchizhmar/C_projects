
TARGET = my_cat

CC = gcc -Werror -Wextra -Wall

all: my_cat

clean:
	rm -rf *.o $(TARGET)

my_cat:
	$(CC) -o $(TARGET) my_cat.c

rebuild: clean all