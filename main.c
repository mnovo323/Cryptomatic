#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "bruteforce.h"
#include "crypto.h"
#define DICT_PATH "/home/zyn/Desktop/spr23/cs430/cryptomatic/Dictionary.txt"
#define CYPHER_TEXT_PATH "/home/zyn/Desktop/spr23/cs430/cryptomatic/LincolnEncrypted.txt"

int main(int argc, char **argv)
{
	struct ht *lookup_table = load_dict(DICT_PATH, 1610333);

	struct buff *buff = read_file(CYPHER_TEXT_PATH);
	
	miketheripper(buff, lookup_table);


	return 0;
}
