#include "strqueue.h"
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>
#include <string>

using namespace std;

static unordered_map<unsigned long, deque<string>> Map;

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
    if (debug)
        cerr << "strqueue_get_at(" << id << ", " << position << ")\n";

    auto it = Map.find(id);
    auto MainQueue = it->second;

    if (it != Map.end() && position < MainQueue.size()) {
        size_t i = 0;
        stack<string> SupportStack;

        while (i < position) {
            SupportStack.push(MainQueue.front());
            MainQueue.pop_front();
            i++;
        }

        string ans = MainQueue.front();

        while (!SupportStack.empty()) {
            MainQueue.push_front(SupportStack.top());
            SupportStack.pop();
        }

        if (debug)
            cerr << "strqueue_get_at returns \"" << ans << "\"\n";

        return ans.c_str();
    }
    else if (debug) {
        if (it == Map.end())
            cerr << "strqueue_get_at: queue " << id << " does not exist\n";
        else if (position >= MainQueue.size())
            cerr << "strqueue_get_at: queue " << id << " does not contain string at position " << position <<"\n";

        cerr << "strqueue_get_at returns NULL\n";
    }

    return NULL;
}

void strqueue_clear(unsigned long id) {
    // TODO    
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    // TODO
}