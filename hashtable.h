#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h> /* size_t */
#include <stdbool.h> /* bool */
struct ht {
	char **vals;
	size_t n;
};
struct ht *ht_init(size_t);
void       ht_dstr(struct ht**);
void        ht_put(char*, struct ht*);
bool        ht_has(char*, struct ht*);
#endif
