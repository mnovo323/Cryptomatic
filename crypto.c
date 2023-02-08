#include <stdint.h> /* uint16_t */
#include <stdlib.h> /* size_t, malloc, calloc, memcpy */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
struct ct {
	uint16_t *m;
	size_t n;
};

void ct_destr(struct ct** ct)
{
	free((*ct)->m);
	free(*ct);
}

void xcrypt(uint16_t k, struct ct *m)
{
	for (size_t i = 0; i < m->n; i++) {
		m->m[i] ^= k;
	}
}

struct ct *parse(char *m, size_t n)
{
	size_t l = n;
	if (n % 2)
		++l;
	uint16_t *ptxt = calloc(l, 1);
	memcpy(ptxt, m, n);
	struct ct *pm = malloc(sizeof(struct ct));
	pm->m = ptxt;
	pm->n = l / 2;
	return pm;
}

char *ct_to_str(struct ct* ct)
{
	char *buffer = malloc(ct->n * 2);
	for (size_t i = 0; i < ct->n; i++) {
		buffer[i * 2] = (char)((ct->m[i] & 0xFF));
		buffer[(i * 2) + 1] = (char)((ct->m[i] & 0xFF00) >> 8);
	}
	return buffer;
}


uint16_t key(char *k)
{
	return (uint16_t) ((uint16_t)*k << 8 ) | ((uint16_t) *(k + 1));
}
