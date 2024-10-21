.PHONY: clean

# Kompilator
CPP = g++
CC = gcc
# Flagi
CFLAGS = -Wall -Wextra -O2 -std=c17
CPPFLAGS = -Wall -Wextra -O2 -std=c++17
NDBG = -DNDEBUG

all: strqueue_test_1_dbg strqueue_test_1_nodbg strqueue_test_2_dbg_a strqueue_test_2_dbg_b strqueue_test_2_nodbg

strqueue_dbg.o: strqueue.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

strqueue_nodbg.o: strqueue.cpp
	$(CPP) -c $(CPPFLAGS) $(NDBG) $< -o $@

strqueue_test_1.o: strqueue_test_1.c
	$(CC) -c $(CFLAGS) $< -o $@

strqueue_test_2.o: strqueue_test_2.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

strqueue_test_1_dbg: strqueue_test_1.o strqueue_dbg.o
	$(CPP) $< -o $@

strqueue_test_1_nodbg: strqueue_test_1.o strqueue_nodbg.o
	$(CPP) $< -o $@

strqueue_test_2_dbg_a: strqueue_test_2.o strqueue_dbg.o
	$(CPP) $< -o $@

strqueue_test_2_dbg_b: strqueue_dbg.o strqueue_test_2.o
	$(CPP) $< -o $@

strqueue_test_2_nodbg: strqueue_test_2.o strqueue_nodbg.o
	$(CPP) $< -o $@

clean:
	rm -f *.o