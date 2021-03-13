#pragma once

#include "my_string.h"

struct IO {
	void* opaque; 
	
	struct String* (*getword) (struct IO* this);
};

struct IO* new_IO(const char* path);
void delete_IO(struct IO* this);
