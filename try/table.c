/*
 * table.c
 *
 *  Created on: Jul 17, 2015
 *      Author: student
 */


#include "table.h"

struct table *build_table(size_t size) {
	struct table *table = malloc(sizeof(struct table));
	table->size = size;
	table->data = calloc(size , sizeof(struct hand *));
	return table;
}

int hash_key(struct table *table, char *name) {
	int count = 0;
	while(*name) {
		count += *name;
		name++;
	}
	return count %table->size;
}
struct hand *fetch_table(struct table *table, char *name){
	if(!table || !name) {
		return NULL;
	}
	int n = hash_key(table, name);
	return table->data[n];


}

void store_table(struct table *table, char *name, struct hand *hand) {
	if(!table || !name) {
		return;
	}
	int n = hash_key(table, name);
	table->data[n] = hand;


}

void free_table(struct table *table) {
	free(table->data);
	free(table);
}
