#include <stdint.h> /* uint64_t */
#include <stdlib.h> /* size_t, calloc, malloc, free */
#include <string.h> /* strcmp */
#include <stdbool.h> /* bool, true, false */
#include <stdio.h>
#include "hashtable.h"
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-= ABOUT THIS FILE =-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* Strictly speaking (okay, speaking any kind of way), this is NOT a hash table
 * I only call it that because, well, I'm not sure what else to call it. The
 * sole purpose of this data structure (and the algorithms that go with it) is
 * to check if a given string is in a set in constant time. 
 */

/* -=-=-=-=-=-= STRUCT DEFINITIONS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

/* struct ht {
	char **vals;
	size_t n;
}; */

/* -=-=-=-=-=-=-=-=-=-=-= INTERNAL METHODS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

/*
 * "This algorithm (k=33) was first reported by dan bernstein many years ago
 * in comp.lang.c. another version of this algorithm (now favored by bernstein)
 * uses xor: ... the magic of number 33 (why it works better than many other
 * constants, prime or not) has never been adequately explained."
 *
 * Source: www.cse.yorku.ca/~oz/hash.html
 *
 * I just needed a good hash for strings, and this one seems reasonable.
 */
static uint64_t djb2(char *str)
{
	uint64_t hash = 5381;
	char c;
	while (c = *str++) {
		/* 
		 * x << 5 == x * 2**5 == x * 32
		 * by adding the value again:
		 * (x << 5) + x == (x * 32) + x == 33 * x
		 * but with the benefit of bitwise operations being fast
		 */
		hash = ((hash << 5) + hash) ^ c;
	}
	return hash;
}

/* -=-=-=-=-=-=-=-=-=-=-=- PUBLIC METHODS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*
 * I HEREBY DECLARE THAT N SHALL BE A PRIME NUMBER APPROXIMATELY 2-3 TIMES HOW
 * MANY ITEMS YOU PLAN ON STORING.
 */
struct ht *ht_init(size_t n)
{
	char **vals = calloc(n, sizeof(char*));
	struct ht *ht = malloc(sizeof(struct ht));
	ht->vals = vals;
	ht->n = n;
	return ht;
}

void ht_dstr(struct ht **ht)
{
	for (size_t i = 0; i < (*ht)->n; i++) {
		free((*ht)->vals[i]);
		(*ht)->vals[i] = NULL;
	}
	free((*ht)->vals);
	(*ht)->vals = NULL;
	free(*ht);
	*ht = NULL;
}

void ht_put(char *v, struct ht *ht)
{
	uint64_t hash = djb2(v);
	size_t idx = hash % ht->n;
	while (ht->vals[idx] != NULL) {
		if (!(strcmp(ht->vals[idx], v))) {
			printf("v: \n");
			printf("t: %s\n", ht->vals[idx]);
			return;
		}
		idx++;
	}
	ht->vals[idx] = v;
}

bool ht_has(char *v, struct ht *ht)
{
	uint64_t hash = djb2(v);
	size_t idx = hash % ht->n;
	while (ht->vals[idx] != NULL) {
		if (!(strcmp(ht->vals[idx], v)))
			return true;
		idx++;
	}
	return false;
}
