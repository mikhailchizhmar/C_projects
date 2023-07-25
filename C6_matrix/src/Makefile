CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
OS = $(shell uname)
FILES_C = my_matrix.c help.c
FILES_A = my_matrix.a
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

TEST_COMPILE = $(CC+FLAGS) $(FILES_A) tests.c $(CHECK_FLAGS) -L. $(FILES_A)

all: clean $(FILES_A) test gcov_report

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM

test: $(FILES_A)
	$(TEST_COMPILE)
	./a.out

gcov_report: test
	rm -f *.g*
	$(CC+FLAGS) $(FILES_C) tests.c $(FILES_A) $(CHECK_FLAGS) $(GCOVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

main:
	make clean
	$(CC+FLAGS) -c $(FILES_C) main.c
	ar rcs $(FILES_A) *.o
	rm -rf *.o
	ranlib $(FILES_A)
	$(CC+FLAGS) $(FILES_A) $(CHECK_FLAGS) -L. $(FILES_A)
	./a.out

$(FILES_A):
	$(CC+FLAGS) -c $(FILES_C)
	ar rcs $(FILES_A) *.o
	rm -rf *.o
	ranlib $(FILES_A)

check:
ifeq ("","$(wildcard ./.clang-format)")
	cp -f ../materials/linters/.clang-format ./.clang-format
endif
	clang-format -n *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind  --leak-check=full --track-origins=yes ./a.out
endif
	make clean

style:
	clang-format -i *.c *.h