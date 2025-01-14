#include "strqueue.h"
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>
#include <string>
#include <climits>
#include <cassert>

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
using std::min;

// anonymous namespace for helper functions
namespace {
    // Holds all strqueues indexed by their IDs.
    unordered_map<unsigned long, deque<string>>& strqueue_map() {
        static unordered_map<unsigned long, deque<string>>* strqueue_map = 
                        new unordered_map<unsigned long, deque<string>>();
        return *strqueue_map;
    }

    // function that initializes stderr
    void initializeCerr() {

        // to ensure initialization happens only once
        static bool isInitialized = false; 

        if (!isInitialized) {
            std::ios_base::Init manualInit;
            isInitialized = true;
        }

    }

    // Variadic logging function used if debug mode is on
    template<typename... Args>
    void LOG_MESSAGE(Args... args) {
        if constexpr (debug) {
            initializeCerr();
            (std::cerr << ... << args);
        }
    }
}

unsigned long strqueue_new() {
    static unsigned long currId = 0;
    LOG_MESSAGE("strqueue_new()\n");

    // check for overflows
    [[maybe_unused]] static bool isMax = false;
    assert(!isMax);
    isMax = currId == ULONG_MAX;

    strqueue_map()[currId] = deque<string>();
    currId++;
    LOG_MESSAGE("strqueue_new returns ", currId - 1, "\n");
    return currId - 1;
}

void strqueue_delete(unsigned long id) {
    LOG_MESSAGE("strqueue_delete(", id, ")\n");

    size_t answer = strqueue_map().erase(id);

    if (answer > 0)
        LOG_MESSAGE("strqueue_delete done\n");
    else
        LOG_MESSAGE("strqueue_delete: queue ", id, " does not exist\n");
}

size_t strqueue_size(unsigned long id) {
    LOG_MESSAGE("strqueue_size(", id, ")\n");

    const auto answer_iterator = strqueue_map().find(id);

    if (answer_iterator == strqueue_map().end()) {
        LOG_MESSAGE("strqueue_size: queue ", id, " does not exist\n");
        LOG_MESSAGE("strqueue_size returns 0\n");
        return 0;
    }

    size_t answer = answer_iterator->second.size();
    LOG_MESSAGE("strqueue_size returns ", answer, "\n");
    return answer;
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    LOG_MESSAGE("strqueue_insert_at(", id, ", ", position, ", ");
    if (str == NULL) {
        LOG_MESSAGE("NULL)\n");
    }
    else {
        LOG_MESSAGE("\"", str, "\")\n");
    }

    const auto it = strqueue_map().find(id);
    
    if (it != strqueue_map().end() && str != NULL) {
        auto& currQueue = it->second;

        // insert at position or at the end (if position is bigger than queue size)
        currQueue.insert(currQueue.begin() + min(position, currQueue.size()), str);

        LOG_MESSAGE("strqueue_insert_at done\n");
    }
    else {
        LOG_MESSAGE("strqueue_insert_at");
        if (it == strqueue_map().end()) {
            LOG_MESSAGE(": queue ", id, " does not exist\n");
        }
        else if (str == NULL) {
            LOG_MESSAGE(" failed\n");
        }
    }
}

void strqueue_remove_at(unsigned long id, size_t position) {

    LOG_MESSAGE("strqueue_remove_at(", id, ", ", position, ")\n");
    
    const auto it = strqueue_map().find(id);
    if (it == strqueue_map().end()) {
        LOG_MESSAGE("strqueue_remove_at: queue ", id, " does not exist\n");
        return;
    }
    auto& currQueue = it->second;
    if (position >= currQueue.size()) { // check if position is valid
        LOG_MESSAGE("strqueue_remove_at: queue ", id, 
                    " does not contain string at position ", position, "\n");
        return;
    }

    currQueue.erase(currQueue.begin() + position);

    LOG_MESSAGE("strqueue_remove_at done\n");

}

const char* strqueue_get_at(unsigned long id, size_t position) {
    LOG_MESSAGE("strqueue_get_at(", id, ", ", position, ")\n");

    const auto it = strqueue_map().find(id);

    if (it != strqueue_map().end() && position < it->second.size()) {
        auto& currQueue = it->second;
        deque<string>::iterator deque_it = currQueue.begin() + position;

        string& ans = *deque_it;

        LOG_MESSAGE("strqueue_get_at returns \"", ans, "\"\n");
        return ans.c_str();
    }
    else {
        LOG_MESSAGE("strqueue_get_at: queue ", id);
        if (it == strqueue_map().end())
            LOG_MESSAGE(" does not exist\n");
        else
            LOG_MESSAGE(" does not contain string at position ", position, "\n");
        LOG_MESSAGE("strqueue_get_at returns NULL\n");
    }

    return NULL;
}

void strqueue_clear(unsigned long id) {
    LOG_MESSAGE("strqueue_clear(", id, ")\n");
    
    const auto it_dq = strqueue_map().find(id);

    if (it_dq == strqueue_map().end()) {
        LOG_MESSAGE("strqueue_clear: queue ", id, " does not exist\n");
        return;
    }
    
    (it_dq->second).clear();
    
    LOG_MESSAGE("strqueue_clear done\n");
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    LOG_MESSAGE("strqueue_comp(", id1, ", ", id2, ")\n");
    
    const auto it_deque1 = strqueue_map().find(id1);
    const auto it_deque2 = strqueue_map().find(id2);

    // if queue doesn't exist then we consider it as empty
    const auto& deque1 = it_deque1 != strqueue_map().end() ? it_deque1->second : deque<string>();
    const auto& deque2 = it_deque2 != strqueue_map().end() ? it_deque2->second : deque<string>();

    if (it_deque1 == strqueue_map().end()) 
        LOG_MESSAGE("strqueue_comp: queue ", id1, " does not exist\n");
    if (it_deque2 == strqueue_map().end())
        LOG_MESSAGE("strqueue_comp: queue ", id2, " does not exist\n");

    // compare queues lexicographically
    if (deque1 < deque2) {
        LOG_MESSAGE("strqueue_comp returns -1\n");
        return -1;
    }
    else if (deque1 > deque2) {
        LOG_MESSAGE("strqueue_comp returns 1\n");
        return 1;
    } else {
        LOG_MESSAGE("strqueue_comp returns 0\n");
        return 0;
    }
}
}
