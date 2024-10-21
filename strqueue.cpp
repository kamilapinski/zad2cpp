#include "strqueue.h"
#include <unordered_map>
#include <deque>

using namespace std;

static unordered_map<int, deque<string>> Map;

unsigned long strqueue_new() {
    // TODO
}

void strqueue_delete(unsigned long id) {
    // TODO
}

size_t strqueue_size(unsigned long id) {
    // TODO
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    // TODO
}

void strqueue_remove_at(unsigned long id, size_t position) {
    // TODO
}

const char* strqueue_get_at(unsigned long id, size_t position) {
    // TODO
}

void strqueue_clear(unsigned long id) {
    // TODO    
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    // TODO
}