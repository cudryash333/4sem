#pragma once

#include "my_string.h"

struct Map {
	void* opaque; 

	int (*get) (struct Map* this, struct String* key);
	void (*set) (struct Map* this, struct String* key, int val);
	void (*print) (struct Map* this);
};

struct Map* new_Map();
void delete_Map(struct Map* this);
