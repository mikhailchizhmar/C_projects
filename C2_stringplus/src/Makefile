CC = gcc -Wextra -Werror -Wall -std=c11
SOURSE_code = my_strerror.c my_memset.c \
		 my_strcat.c my_strncat.c \
		 my_strchr.c my_memchr.c \
		 my_memcmp.c my_memcpy.c \
		 my_strlen.c my_memmove.c \
		 my_strcspn.c my_strpbrk.c \
		 my_strcmp.c my_strncmp.c \
		my_strcpy.c my_strncpy.c \
		my_strrchr.c my_strspn.c \
		my_strstr.c my_strtok.c \
		my_insert.c my_trim.c \
		my_to_lower.c my_to_upper.c \
		my_sprintf.c my_sscanf.c
OBJECTS_code = $(SOURSE_code:%.c=%.o)
SOURCE_tests = *.c 


all: my_string.a test gcov_report

my_string.a: $(OBJECTS_code)
	ar rcs my_string.a $^
	ranlib my_string.a
	rm *.o
%.o: %.c
	$(CC) -o $@ -c $<
test: 
	$(CC) -lgcov -coverage  $(SOURCE_tests) -lm \
	 -lcheck $(shell pkg-config --cflags --libs check) -o test
	./test
gcov_report: test
	lcov -t "test" -o test.info -c -d . 
	genhtml -o test_output test.info
	@cd ./test_output ; open index.html
clean:
	rm -rf ./test_output/
	rm *.a test *.gcda *.gcno *.info \
	RESULT_VALGRIND.txt test_leaks
valgrind: 
	$(CC) $(SOURCE_tests) -lm \
	 -lcheck $(shell pkg-config --cflags --libs check) -o test_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes\
	 --verbose --log-file=RESULT_VALGRIND.txt ./test_leaks
	 grep "ERROR" RESULT_VALGRIND.txt