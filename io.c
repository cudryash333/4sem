#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my_string.h"
#include "io.h"

struct IOPrivate {
	FILE *file;
};

struct String* IO_get_word(struct IO *this)
{
	struct IOPrivate *private = (struct IOPrivate *)this->opaque;

	char str[100];
	int letter;
	int i = 0;
	letter = fgetc(private->file);
	while ((letter == ' ') || (letter == '\n')) {
		letter = fgetc(private->file);
	}
	if (letter == EOF) {
		return NULL;
	}
	ungetc(letter, private->file);
	letter = fgetc(private->file);
	while ((letter != ' ') && (letter != EOF) && (letter != '\n')
	       && (letter != '\0')) {
		str[i] = letter;
		++i;
		letter = fgetc(private->file);
	}
	str[i] = '\0';
	return new_String(str);
}

struct IO* new_IO(const char *path)
{
	struct IO *res = (struct IO *)malloc(sizeof(struct IO));
	struct IOPrivate *private =
	    (struct IOPrivate *)malloc(sizeof(struct IOPrivate));

	private->file = fopen(path, "r");
	if (!private->file) {
		perror("read_fail:");
	}
	res->opaque = private;
	res->getword = IO_get_word;
	return res;
}

void delete_IO(struct IO *this)
{
	struct IOPrivate *private = (struct IOPrivate *)this->opaque;

	fclose(private->file);
	free(private);
	free(this);
}
