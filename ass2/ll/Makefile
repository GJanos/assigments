ASSIGNMENT=ll
ASSIGNMENT_TEST=ll_test

UNITY_FOLDER=Unity
INC_DIRS=-Iproduct
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=product/linkedlist.c

PRODUCT_FILES=$(SHARED_FILES) 

TEST_FILES=$(SHARED_FILES) \
	        $(UNITY_FOLDER)/unity.c \
	        test/ll_test.c

HEADER_FILES=product/*.h

CC=gcc

SYMBOLS=-g  -O0 -std=c99 -Wall -Werror -pedantic

TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean $(ASSIGNMENT_TEST)

all: $(ASSIGNMENT_TEST)

$(ASSIGNMENT_TEST): Makefile $(TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(TEST_FILES) -o $(ASSIGNMENT_TEST)

test: $(ASSIGNMENT_TEST)
	@./$(ASSIGNMENT_TEST)

valgrind: $(ASSIGNMENT_TEST)
	valgrind --leak-check=yes ./ll_test

clean:
	@rm -f $(ASSIGNMENT_TEST)
	@rm -rf kwinject.out .kwlp .kwps

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
