/*
 * table.h
 *
 *  Created on: Jul 17, 2015
 *      Author: student
 */

#ifndef TABLE_H_
#define TABLE_H_
#include "hand.h"
#include <stdlib.h>
struct table {
	struct hand **data;
	size_t size;

};
//Creates a new table structure of size entries
struct table *build_table(size_t size);
//Will store a hand at key name within the table
void store_table(struct table *table, char *name, struct hand *hand);
//Will get the value stored in the table
struct hand *fetch_table(struct table *table, char *name);
//Frees a table structure
void free_table(struct table *table);


#endif /* TABLE_H_ */
