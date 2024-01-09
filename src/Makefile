CC = gcc -std=c++17 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES = s21_matrix_oop.cc s21_matrix_oop_tests.cc

ifeq ($(OS), Linux)
	CHECKFLAGS=-lgtest -lgtest_main -lrt -lm -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: test
	

s21_matrix_oop.a:
	$(CC) $(FLAGS) -c s21_matrix_oop.cc
	ar -crs libs21_matrix_oop.a s21_matrix_oop.o

test: clean
	$(CC) $(FLAGS) $(LIBSOURCES) -o a.out $(CHECKFLAGS) -lgcov --coverage
	./a.out

gcov_report: test
	lcov --no-external -t "test" -o report.info -c -d . --ignore-errors mismatch
	genhtml -o report report.info
	open ./report/index.html

test_leaks: test
	leaks --atExit -- ./a.out


valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./a.out

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n s21_matrix_oop.* s21_matrix_oop_tests.cc

clean:
	rm -rf report \
	*.a \
	*.info \
	*.gcda \
	*.gcno \
	*.o \
	*.dSYM \
	a.out