#include "strqueue.h"
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>

using namespace std;

static unordered_map<int, deque<string>> Map;

unsigned long strqueue_new() {
    // TODO
}

void strqueue_delete(unsigned long id) {
    if (debug) cerr << "strqueue_delete(" << id << ")\n";
    size_t answer = Map.erase(id);
    if (debug) {
        if (answer > 0)
            cerr << "strqueue_delete done\n";
        else
            cerr << "strqueue_delete failed\n";
    }
}

size_t strqueue_size(unsigned long id) {
    // TODO
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    if (debug) 
        cerr << "strqueue_insert_at(" << id << ", " << position << ", " << str << ")\n";

    auto it = Map.find(id);

    if (it != Map.end() && str != NULL) {
        auto MainQueue = it->second;
        size_t i = MainQueue.size() - 1;

        stack<string> SupportStack;

        while (i >= position) {
            SupportStack.push(MainQueue.back());
            MainQueue.pop_back();
            i--;
        }

        MainQueue.push_back(str);

        while (!SupportStack.empty()) {
            MainQueue.push_back(SupportStack.top());
            SupportStack.pop();
        }

        if (debug)
            cerr << "strqueue_insert_at done\n";
    }
    else if (debug)
        cerr << "strqueue_insert_at failed\n";
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