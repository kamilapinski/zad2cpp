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

        string& ans = MainQueue.front();

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
    if (debug)
        cerr << "strqueue_comp(" << id1 << ", " << id2 << ")\n";

    deque<string> Deque1 = Map[id1]; 
    deque<string> Deque2 = Map[id2]; 

    if (debug) {
        if (Deque1.empty()) cerr << "strqueue_comp: queue 1 does not exist\n";
        if (Deque2.empty()) cerr << "strqueue_comp: queue 2 does not exist\n";
    }

    deque<string>::iterator it1 = Deque1.begin();
    deque<string>::iterator it2 = Deque2.begin();

    while (it1 < Deque1.end() && it2 < Deque2.end() && (*it1).compare(*it2) == 0)
        it1++, it2++;

    if (it1 < Deque1.end() && it2 < Deque2.end()) {
        if ((*it1).compare(*it2) < 0) {
            if (debug) cerr << "strqueue_comp returns -1\n";
            return -1;
        }
        else {
            if (debug) cerr << "strqueue_comp returns 1\n";
            return 1;
        }
    }
    else if (it1 < Deque1.end()) {
        if (debug) cerr << "strqueue_comp returns 1\n";
        return 1;
    }
    else if (it2 < Deque2.end()) {
        if (debug) cerr << "strqueue_comp returns -1\n";
        return -1;
    }
    else {
        if (debug) cerr << "strqueue_comp returns 0\n";
        return 0;
    }
}