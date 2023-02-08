#ifndef CRYTPO_H
#define CRYPTO_H
#include <stdint.h>
#include <stdlib.h>
struct ct {
	uint16_t *m;
	size_t n;
};
void xcrypt(uint16_t, struct ct*);
struct ct *parse(char*, size_t);
void ct_destr(struct ct**);
uint16_t key(char*);
char *ct_to_str(struct ct*);
#endif
