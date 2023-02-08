#ifndef BRUTEFORCE_H
#define BRUTEFORCE
#include <stdbool.h> /* bool */
#include <stdlib.h> /* size_t */
#include "hashtable.h" /* ht */
bool BF_ENGL_FLAG;
bool BF_ASCII_FLAG;
struct ht *load_dict(const char*, size_t);
struct buff {
	char *buffer;
	size_t len;
};
struct buff *read_file(const char*);
void miketheripper(struct buff*, struct ht*);

#endif
