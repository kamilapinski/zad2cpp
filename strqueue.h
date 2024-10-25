#ifndef STRQUEUE_H
#define STRQUEUE_H

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    unsigned long strqueue_new();
    void strqueue_delete(unsigned long id);
    size_t strqueue_size(unsigned long id);
    void strqueue_insert_at(unsigned long id, size_t position, const char* str);
    void strqueue_remove_at(unsigned long id, size_t position);
    const char* strqueue_get_at(unsigned long id, size_t position);
    void strqueue_clear(unsigned long id);
    int strqueue_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace cxx {
    inline unsigned long strqueue_new() { return ::strqueue_new(); }
    inline void strqueue_delete(unsigned long id) { ::strqueue_delete(id); }
    inline size_t strqueue_size(unsigned long id) { return ::strqueue_size(id); }
    inline void strqueue_insert_at(unsigned long id, size_t position, const char* str) { ::strqueue_insert_at(id, position, str); }
    inline void strqueue_remove_at(unsigned long id, size_t position) { ::strqueue_remove_at(id, position); }
    inline const char* strqueue_get_at(unsigned long id, size_t position) { return ::strqueue_get_at(id, position); }
    inline void strqueue_clear(unsigned long id) { ::strqueue_clear(id); }
    inline int strqueue_comp(unsigned long id1, unsigned long id2) { return ::strqueue_comp(id1, id2); }
}
#endif

#endif // STRQUEUE_H

#ifndef NDEBUG
    const bool debug = false;
#else
    const bool debug = true;
#endif