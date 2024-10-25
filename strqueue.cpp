#include "strqueue.h"
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>
#include <string>

using namespace std;

static unordered_map<unsigned long, deque<string>> Map;

unsigned long strqueue_new() {
    if (debug) cerr << "strqueue_new()\n";
    static unsigned long currId = 0;
    Map[currId] = deque<string>();
    currId++;
    if (debug) cerr << "strqueue_new returns " << currId - 1;
    return currId - 1;
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
    if (debug) cerr << "strqueue_size(" << id << ")\n";
    const auto answer_iterator = Map.find(id);
    if (answer_iterator == Map.end()) {
        if (debug)
            cerr << "strqueue_size: queue " << id << " does not exist\n"
                 << "strqueue_size returns 0";

        return 0;
    }
    size_t answer = answer_iterator->second.size();
    if (debug)
        cerr << "strqueue_size returns " << answer;
    return answer;
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
    if (debug)
        cerr << "strqueue_remove_at(" << id << ", " << position << ")\n";
    
    const auto it = Map.find(id);
    if (it == Map.end()) {
        if (debug)
            cerr << "strqueue_remove_at: queue " << id << " does not exist";
        return;
    }
    auto currQueue = it->second;
    if (position >= currQueue.size()) {
        cerr << "strqueue_remove_at: queue " << id 
             << " does not contain string at position " << position;
            return;
    }

    size_t counter = 0;
    stack<string> SupportStack;

    while (counter < position) {
        SupportStack.push(currQueue.front());
        currQueue.pop_front();
        counter++;
    }

    currQueue.pop_front();

    while (!SupportStack.empty()) {
        currQueue.push_front(SupportStack.top());
        SupportStack.pop();
    }

    if (debug) {
        cerr << "strqueue_remove_at done";
    }

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
    if (debug)
        cerr << "stqueue_clear(" << id << ")";
    
    const auto it_dq = Map.find(id);

    if (it_dq == Map.end()) {
        if (debug)
            cerr << "strqueue_clear: queue " << id << " does not exist\n";
        return;
    }
    
    deque<string> currQueue = it_dq->second;
    
    while (!currQueue.empty()) {
        currQueue.pop_back();
    }
    cerr << "strqueue_clear done\n";
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    if (debug)
        cerr << "strqueue_comp(" << id1 << ", " << id2 << ")\n";

    const auto it_dq1 = Map.find(id1);
    const auto it_dq2 = Map.find(id2);

    deque<string> Deque1, Deque2;

    if (it_dq1 == Map.end()) {
        Deque1 = deque<string>();
        if (debug) cerr << "strqueue_comp: queue " << id1 << " does not exist\n";
    }
    if (it_dq2 == Map.end()) {
        Deque2 = deque<string>();
        if (debug) cerr << "strqueue_comp: queue " << id2 << " does not exist\n";
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
