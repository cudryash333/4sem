#pragma once

struct String
{
    void* opaque;

    void (*print) (struct String* this);
    int (*compare) (struct String* this, struct String* other);
    struct String* (*copy) (struct String* src);
};

struct String* new_String(char* string);
void delete_String(struct String* this);
