#include "strqueue.h"
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>
#include <string>

namespace cxx {

#ifndef NDEBUG
    const bool debug = true;
#else
    const bool debug = false;
#endif

using std::cerr;
using std::unordered_map;
using std::deque;
using std::string;
using std::stack;

// map that contains all strqueues
unordered_map<unsigned long, deque<string>>& map() {
    static unordered_map<unsigned long, deque<string>>* map = new unordered_map<unsigned long, deque<string>>();
    return *map;
}

// function that initializes stderr
void initializeCerr() {
    if constexpr (debug) {
        static bool isInitialized = false;
        if (!isInitialized) {
            std::ios_base::Init manualInit;
            isInitialized = true;
        }
    }
}

unsigned long strqueue_new() {
    initializeCerr();
    if constexpr (debug) cerr << "strqueue_new()\n";
    static unsigned long currId = 0;
    map()[currId] = deque<string>();
    currId++;
    if constexpr (debug) cerr << "strqueue_new returns " << currId - 1 << "\n";
    return currId - 1;
}

void strqueue_delete(unsigned long id) {
    initializeCerr();
    if constexpr (debug) cerr << "strqueue_delete(" << id << ")\n";

    size_t answer = map().erase(id);
    if constexpr (debug) {
        if (answer > 0)
            cerr << "strqueue_delete done\n";
        else
            cerr << "strqueue_delete: queue " << id << " does not exist\n";
    }
}

size_t strqueue_size(unsigned long id) {
    initializeCerr();
    if constexpr (debug) cerr << "strqueue_size(" << id << ")\n";
    const auto answer_iterator = map().find(id);
    if (answer_iterator == map().end()) {
        if constexpr (debug)
            cerr << "strqueue_size: queue " << id << " does not exist\n"
                 << "strqueue_size returns 0\n";

        return 0;
    }
    size_t answer = answer_iterator->second.size();
    if constexpr (debug)
        cerr << "strqueue_size returns " << answer << "\n";
    return answer;
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    initializeCerr();
    if constexpr (debug) {
        cerr << "strqueue_insert_at(" << id << ", " << position << ", ";
        if (str == NULL) {
            cerr << "NULL";
        }
        else {
            cerr << "\"" << str << "\"";
        }
        cerr << ")\n";
    }

    const auto it = map().find(id);

    if (it != map().end() && str != NULL) {
        auto& currQueue = it->second;
        size_t i = currQueue.size();

        stack<string> supportStack;

        while (i > position) {
            supportStack.push(currQueue.back());
            currQueue.pop_back();
            i--;
        }

        currQueue.push_back(str);

        while (!supportStack.empty()) {
            currQueue.push_back(supportStack.top());
            supportStack.pop();
        }

        if constexpr (debug)
            cerr << "strqueue_insert_at done\n";
    }
    else if constexpr (debug) {
        cerr << "strqueue_insert_at";
        if (it == map().end()) {
            cerr << ": queue " << id << " does not exist";
        }
        else if (str == NULL) {
            cerr << " failed";
        }
        cerr << "\n";
    }
}

void strqueue_remove_at(unsigned long id, size_t position) {
    initializeCerr();
    if constexpr (debug)
        cerr << "strqueue_remove_at(" << id << ", " << position << ")\n";
    
    const auto it = map().find(id);
    if (it == map().end()) {
        if constexpr (debug)
            cerr << "strqueue_remove_at: queue " << id << " does not exist\n";
        return;
    }
    auto& currQueue = it->second;
    if (position >= currQueue.size()) {
        if constexpr (debug)
            cerr << "strqueue_remove_at: queue " << id 
             << " does not contain string at position " << position << "\n";
        return;
    }

    size_t counter = 0;
    stack<string> supportStack;

    while (counter < position) {
        supportStack.push(currQueue.front());
        currQueue.pop_front();
        counter++;
    }

    currQueue.pop_front();

    while (!supportStack.empty()) {
        currQueue.push_front(supportStack.top());
        supportStack.pop();
    }

    if constexpr (debug) {
        cerr << "strqueue_remove_at done\n";
    }

}

const char* strqueue_get_at(unsigned long id, size_t position) {
    initializeCerr();
    if constexpr (debug)
        cerr << "strqueue_get_at(" << id << ", " << position << ")\n";

    const auto it = map().find(id);
    auto& currQueue = it->second;

    if (it != map().end() && position < currQueue.size()) {
        deque<string>::iterator deque_it = currQueue.begin() + position;

        string& ans = *deque_it;

        if constexpr (debug)
            cerr << "strqueue_get_at returns \"" << ans << "\"\n";

        return ans.c_str();
    }
    else if constexpr (debug) {
        if (it == map().end())
            cerr << "strqueue_get_at: queue " << id << " does not exist\n";
        else if (position >= currQueue.size())
            cerr << "strqueue_get_at: queue " << id << " does not contain string at position " << position <<"\n";

        cerr << "strqueue_get_at returns NULL\n";
    }

    return NULL;
}

void strqueue_clear(unsigned long id) {
    initializeCerr();
    if constexpr (debug)
        cerr << "strqueue_clear(" << id << ")\n";
    
    const auto it_dq = map().find(id);

    if (it_dq == map().end()) {
        if constexpr (debug)
            cerr << "strqueue_clear: queue " << id << " does not exist\n";
        return;
    }
    
    deque<string>& currQueue = it_dq->second;
    
    while (!currQueue.empty()) {
        currQueue.pop_back();
    }
    cerr << "strqueue_clear done\n";
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    initializeCerr();
    if constexpr (debug)
        cerr << "strqueue_comp(" << id1 << ", " << id2 << ")\n";

    const auto it_deque1 = map().find(id1);
    const auto it_deque2 = map().find(id2);

    deque<string> deque1, deque2;

    if (it_deque1 == map().end()) {
        deque1 = deque<string>();
        if constexpr (debug) cerr << "strqueue_comp: queue " << id1 << " does not exist\n";
    }
    else {
        deque1 = map()[id1];
    }
    if (it_deque2 == map().end()) {
        deque2 = deque<string>();
        if constexpr (debug) cerr << "strqueue_comp: queue " << id2 << " does not exist\n";
    }
    else {
        deque2 = map()[id2];
    }

    deque<string>::iterator it1 = deque1.begin();
    deque<string>::iterator it2 = deque2.begin();

    while (it1 < deque1.end() && it2 < deque2.end() && (*it1).compare(*it2) == 0)
        it1++, it2++;

    if (it1 < deque1.end() && it2 < deque2.end()) {
        if ((*it1).compare(*it2) < 0) {
            if constexpr (debug) cerr << "strqueue_comp returns -1\n";
            return -1;
        }
        else {
            if constexpr (debug) cerr << "strqueue_comp returns 1\n";
            return 1;
        }
    }
    else if (it1 < deque1.end()) {
        if constexpr (debug) cerr << "strqueue_comp returns 1\n";
        return 1;
    }
    else if (it2 < deque2.end()) {
        if constexpr (debug) cerr << "strqueue_comp returns -1\n";
        return -1;
    }
    else {
        if constexpr (debug) cerr << "strqueue_comp returns 0\n";
        return 0;
    }
}
}
