#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

struct StringPrivate {
	int length;
	char *data;
};

void String_print(struct String *this)
{
	struct StringPrivate *private = (struct StringPrivate *)this->opaque;
	printf("%s", private->data);
}

int String_compare(struct String *this, struct String *other)
{
	struct StringPrivate *private_this =
	    (struct StringPrivate *)this->opaque;
	struct StringPrivate *private_other =
	    (struct StringPrivate *)other->opaque;
	return strcmp(private_this->data, private_other->data);
}

struct String *NewStringCopy(struct String *src)
{
	struct String *this = (struct String *)malloc(sizeof(struct String));
	struct StringPrivate *private_src = (struct StringPrivate *)src->opaque;
	struct StringPrivate *private =
	    (struct StringPrivate *)malloc(sizeof(struct StringPrivate));

	private->length = private_src->length;
	private->data = (char *)malloc(private->length);
	strcpy(private->data, (char *)private_src->data);
	this->opaque = private;

	this->print = String_print;
	this->compare = String_compare;
	this->copy = NewStringCopy;

	return this;
}

struct String *new_String(char *string)
{
	struct String *res = (struct String *)malloc(sizeof(struct String));
	// initialize private data
	struct StringPrivate *private = (struct StringPrivate *)res->opaque;
	private = (struct StringPrivate *)malloc(sizeof(struct StringPrivate));
	private->length = strlen(string);
	private->data = malloc(private->length);
	strcpy(private->data, (char *)string);
	res->opaque = private;
	// initialize methods
	res->print = String_print;
	res->compare = String_compare;
	res->copy = NewStringCopy;
	return res;
}

void delete_String(struct String *this)
{
	struct StringPrivate *private = this->opaque;
	free(private->data);
	free(private);
	free(this);
}
