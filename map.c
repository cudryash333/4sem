#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "map.h"

struct MapPrivate {
	struct Item{
		struct String* key;
		int value;
	} *data;
	int length;
};

int Map_get (struct Map* this, struct String* key) {
	struct MapPrivate* private = (struct MapPrivate*)this->opaque;
	for(int i = 0; i < private->length; i++) {
		if (key->compare(key, private->data[i].key) != 0) continue;
		return private->data[i].value;
	}
	return -1;
}

void Map_set (struct Map* this, struct String* key, int val) {
	struct MapPrivate* private = (struct MapPrivate*)this->opaque;
	for(int i = 0; i < private->length; i++) {
		if (key->compare(key, private->data[i].key) != 0) continue;
		private->data[i].value = val;
		return;
	}
	private->length++;
	private->data = realloc(private->data, sizeof(struct Item) * private->length);
	private->data[private->length - 1].key = key->copy(key);
	private->data[private->length - 1].value = val;
	this->opaque = private;
}

void Map_print(struct Map* this) {
	struct MapPrivate* private = (struct MapPrivate*)this->opaque;
	for (int i = 0; i < private->length; i++) {
		private->data[i].key->print(private->data[i].key);
		printf(": %d\n", private->data[i].value);
	}
}

struct Map* new_Map() {	
	struct Map* res = (struct Map*)malloc(sizeof(struct Map));
	struct MapPrivate* private = (struct MapPrivate*)malloc(sizeof(struct MapPrivate));
	private->length = 0;
	private->data = malloc(0);
	res->get = Map_get;
	res->set = Map_set;
	res->print = Map_print;
}

void delete_Map(struct Map* this) {
	struct MapPrivate* private = (struct MapPrivate*)this->opaque;
	for (int i = 0; i < private->length; i++) {
		delete_String(private->data[i].key);
	}
	free(private->data);
	free(private);
	free(this);
} 

