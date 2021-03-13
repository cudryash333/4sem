#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "io.h"
#include "map.h"

int main(int argc, char **argv) {
	struct IO* io = new_IO(argv[1]);
	struct Map* map = new_Map();
	struct String* word;
	
	while((word = io->getword(io)) != NULL) {
		map->set(map, word, map->get(map, word) + 1);
		delete_String(word);
	}
	map->print(map);
	delete_Map(map);
	delete_IO(io);
	return 0;
}
