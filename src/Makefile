# Variables
CFLAGS = gcc -Wall -Wextra -Werror -std=c11
INFO = report.info
HTML = $(REPORT)/index.html
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
EXCLUDE = --exclude '/usr/*' --exclude '$(TESTS)/*'
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	LIB = -lcheck -lsubunit -lm
else
	LIB = -lcheck
endif

# Folders
TESTS = tests
REPORT = report
GCOV = gcov
OBJ = obj

# Executable files
S21_TEST = s21_test
S21_GCOV = s21_gcov

# Source and objective library files
SRC_NOTATION = *.c
OBJ_NOTATION = *.o
LIB_NOTATION = s21_lib.a

# Source test files
SRC_TEST = $(TESTS)/*.c

INST_DIR=s21_3Dviewer
DIST_DIR=s21_3Dviewer-1.0
# Targets
all : $(LIB_NOTATION) test gcov_report install

$(LIB_NOTATION) :
	$(CFLAGS) -c $(SRC_NOTATION)
	ar rcs $(LIB_NOTATION) $(OBJ_NOTATION)
	ranlib $(LIB_NOTATION)
	mkdir -p $(OBJ)
	mv $(OBJ_NOTATION) $(OBJ)

test : $(LIB_NOTATION)
	$(CFLAGS) $(SRC_TEST) $(LIB_NOTATION) -o $(S21_TEST) $(LIB)
	./$(S21_TEST)

gcov_report :
	$(CFLAGS) $(SRC_NOTATION) $(SRC_TEST) -o $(S21_GCOV) $(LIB) $(GCOV_FLAGS)
	./$(S21_GCOV)
	lcov -c -d . -t "$(REPORT)" -o $(INFO) $(EXCLUDE)
	genhtml -o $(REPORT) $(INFO)
	rm *test*.gc* $(INFO)
	mkdir -p $(GCOV)
	mv *.gc* $(GCOV)
	open $(REPORT)/index.html

open :
	open $(HTML)

style :
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h $(TESTS)/*
uninstall: 
	rm -r $(INST_DIR)
install:	
	mkdir $(INST_DIR)
	cd $(INST_DIR); qmake ../qt/$(INST_DIR)/$(INST_DIR).pro
	cd $(INST_DIR); make
	cd $(INST_DIR); make clean
	open $(INST_DIR)
dist:
	mkdir $(DIST_DIR)
	mkdir $(DIST_DIR)/qt
	cp *.c *.h Makefile $(DIST_DIR)
	cp -R qt $(DIST_DIR)
	tar --totals -cvf $(DIST_DIR).tar $(DIST_DIR)
	rm -rf $(DIST_DIR)
dvi:
	makeinfo manual.texi --html
	open ./manual/index.html 
leaks :
	CK_FORK=no leaks -atExit -q -- ./$(S21_TEST)

valgrind :
	CK_FORK=no valgrind  --track-origins=yes --tool=memcheck --leak-check=yes --show-leak-kinds=all ./$(S21_TEST)

clean :
	rm -rf $(S21_TEST) $(S21_GCOV) $(REPORT) $(OBJ) $(GCOV) *.{a,o,gc*,out,dSYM} .clang-format $(DIST_DIR).tar $(INST_DIR)
	rm -rf s21_notation.a *.tar manual
rebuild :
	make clean
	make all
	
cppcheck:
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem  --suppress=unusedFunction --suppress=invalidPointerCast ./


.PHONY : all clean rebuild $(LIB_NOTATION) test dvi dist gcov_report open style leaks valgrind
