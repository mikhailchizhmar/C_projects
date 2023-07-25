CC:=gcc
CFLAGS := -Wall -Werror -Wextra
GCOV:= #-fprofile-arcs -ftest-coverage

all : clean my_math.a

my_math.a :
	${CC} ${CFLAGS} ${GCOV} -c -o my_math.o my_math.c
	ar rcs my_math.a my_math.o
	ranlib my_math.a

test : all 
	${CC} ${CFLAGS} -c -o tests/my_math_test.o tests/my_math_test.c
	${CC} tests/my_math_test.c my_math.c -lcheck -lm  -o my_math_test.out
	./my_math_test.out

gcov_report:
	${CC} --coverage my_math.c tests/my_math_test.c -o my_test -lcheck
	./my_test
	gcov --stdout my_test
	gcov my_math.c -m
	brew install lcov
	lcov -t "my_test" -o my_test.info -c -d .
	genhtml -o report my_test.info
	open report/index.html

clean :
	rm -f *.html *.css *.gcno *.gcov *.gcda test ./tests/*.gcda ./tests/*.gcno ./tests/*.o *.out *.a *.o gcov_test

rebuild: clean all
