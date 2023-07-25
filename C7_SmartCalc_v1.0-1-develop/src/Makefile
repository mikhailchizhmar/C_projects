CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
OS = $(shell uname)
FILES_C = validation.c parser.c infix_to_rpn.c calculate.c
FILES_A = SmartCalc.a
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

TEST_COMPILE = $(CC+FLAGS) $(FILES_A) tests.c $(CHECK_FLAGS) -L. $(FILES_A)

all: clean $(FILES_A) test gcov_report

install:
	rm -rf build
	mkdir build
	qmake SmartCalc/SmartCalc.pro -o build
	cd build && make && cd ../

dvi:
	open doc.txt

uninstall:
	rm -rf build

dist: install
	tar -czf build.tar.gz --directory=build/ .

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM build.tar.gz

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
