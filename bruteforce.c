#include <stdbool.h> /* bool */
#include <stdlib.h> /* size_t */
#include <stdio.h> /* printf */
#include <string.h> /* strcpy, strsize, strtok */
#include <time.h> /* for timing suite */
#include "hashtable.h" /* ht, ht_get */
#include "crypto.h"

struct buff {
	char *buffer;
	size_t len;
};

/* 1610333 */
struct ht *load_dict(const char *dpath, size_t size)
{
	struct ht *ht = ht_init(size);
	char BUFFER[30];
	FILE *dict = fopen(dpath, "r");
	if (dict == NULL) {
		printf("Error occured reading dictionary file.\n");
		exit(1);
	}
	while (fgets(BUFFER, 30, dict)) {
		size_t len = strlen(BUFFER); /* +1 for null char */
		size_t temp_len = len;
		if (BUFFER[temp_len] == '\r' || BUFFER[temp_len] == '\n') {
			BUFFER[temp_len] = '\0';
			len--;
		}

		if (BUFFER[temp_len - 1] == '\n' || BUFFER[temp_len-1] == '\r') {
			BUFFER[temp_len - 1] = '\0';
			len--;
		}
		if (BUFFER[temp_len - 2] == '\r' || BUFFER[temp_len - 2] == '\n') {
			BUFFER[temp_len - 2] = '\0';
			len--;
		}
		if (BUFFER[temp_len - 3] == '\r' || BUFFER[temp_len - 3] == '\n') {
			BUFFER[temp_len - 3] = '\0';
			len--;
		}

		char *dest = calloc(len, 1);
		strcpy(dest, BUFFER);
		ht_put(dest, ht);
	}
	return ht;
}

struct buff *read_file(const char *fpath)
{
	FILE *f = fopen(fpath, "r");
	if (f == NULL) {
		printf("Error occured opening file.\n");
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	size_t len = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *BUFFER = malloc(len + 1);

	fread(BUFFER, len, 1, f);
	BUFFER[len] = '\0';

	struct buff *buffer = malloc(sizeof(struct buff));
	buffer->buffer = BUFFER;
	buffer->len = len;

	return buffer;
}

void miketheripper(struct buff *b, struct ht *d)
{
	struct buff *nb = malloc(sizeof(struct buff));
	char *nbuffer = malloc(b->len + 1);
	nb->buffer = nbuffer;
	nb->len = b->len;
	memcpy(nbuffer, b->buffer, b->len);
	time_t START_TIME = clock();
	for (char i = 3; i < 127; i++) {
		for (char j = 32; j < 127; j++) {
			char keyc[2];
			keyc[0] = i;
			keyc[1] = j;
			uint16_t k = key(keyc);
			/* printf("key: %u\n", k); */

			struct ct *t = parse(b->buffer, b->len);
			char *delim = " ";
			xcrypt(k, t);
			char* string = ct_to_str(t);
			char *tok = strtok(string, delim);
			unsigned int tok_count = 0;
			while (tok != NULL) {
				/*if(keyc[0] == '~' && keyc[1] == '~') {
					printf("%x\n", k);
					printf("%s\n", tok);
				}*/
				if (ht_has(tok, d)) {
					tok_count++;
					
				}
				if (tok_count >= 9) {
					time_t END_TIME = clock();
					double total_time = ((double) (END_TIME - START_TIME)) / CLOCKS_PER_SEC;
					printf("Time took to brute force:\n");
					printf("%fs\n", total_time);
					printf("%c%c\n", keyc[0], keyc[1]);
					char c = *string;
					for (size_t k = 0; k < b->len; k++) {
						printf("%c", string[k]);
					}
					printf("\n");
					return;
				}
				tok = strtok(NULL, delim);
			}
			ct_destr(&t);
			free(string);

		}
	}
}



/* void bf_file(FILE *f)
{
	switch (BF_ENGL_FLAG << 1 & BF_ASCII_FLAG) {
		case 0x00: 
			break;
		case 0x01:
			break;
		case 0x02:
			break;
		case 0x03:
			break;
		case default:
			break;
}

void bf_stdio();

static void bf_f_xx(FILE *f)
{
}

static void bf_f_xa(FILE *f)
{
}

static void bf_f_ex(FILE *f)
{
}

static void bf_f_ea(FILE *f)
{
} */
