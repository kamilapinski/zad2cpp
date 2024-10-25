# Kompilator i flagi
CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
CFLAGS = -Wall -Wextra -O2 -std=c17

# Pliki źródłowe i obiekty
STRQUEUE_SRC = strqueue.cpp
STRQUEUE_DBG_OBJ = strqueue_dbg.o
STRQUEUE_NODBG_OBJ = strqueue_nodbg.o

TEST1_SRC = strqueue_test_1.c
TEST1_OBJ = strqueue_test_1.o

TEST2_SRC = strqueue_test_2.cpp
TEST2_OBJ = strqueue_test_2.o

# Cele końcowe
TARGETS = strqueue_test_1_dbg strqueue_test_1_nodbg strqueue_test_2_dbg_a strqueue_test_2_dbg_b strqueue_test_2_nodbg

# Domyślny cel
all: $(TARGETS)

# Kompilacja obiektów
$(STRQUEUE_DBG_OBJ): $(STRQUEUE_SRC)
	$(CXX) -c $(CXXFLAGS) $(STRQUEUE_SRC) -o $@

$(STRQUEUE_NODBG_OBJ): $(STRQUEUE_SRC)
	$(CXX) -c $(CXXFLAGS) -DNDEBUG $(STRQUEUE_SRC) -o $@

$(TEST1_OBJ): $(TEST1_SRC)
	$(CC) -c $(CFLAGS) $(TEST1_SRC) -o $@

$(TEST2_OBJ): $(TEST2_SRC)
	$(CXX) -c $(CXXFLAGS) $(TEST2_SRC) -o $@

# Tworzenie programów końcowych
strqueue_test_1_dbg: $(TEST1_OBJ) $(STRQUEUE_DBG_OBJ)
	$(CXX) $^ -o $@

strqueue_test_1_nodbg: $(TEST1_OBJ) $(STRQUEUE_NODBG_OBJ)
	$(CXX) $^ -o $@

strqueue_test_2_dbg_a: $(TEST2_OBJ) $(STRQUEUE_DBG_OBJ)
	$(CXX) $^ -o $@

strqueue_test_2_dbg_b: $(STRQUEUE_DBG_OBJ) $(TEST2_OBJ)
	$(CXX) $^ -o $@

strqueue_test_2_nodbg: $(TEST2_OBJ) $(STRQUEUE_NODBG_OBJ)
	$(CXX) $^ -o $@

# Sprzątanie
clean:
	rm -f $(TARGETS) *.o
