//
// Created by falta on 2/13/2021.
//

#ifndef MD_STRING_READER_H
#define MD_STRING_READER_H

#include <stddef.h>
#include "stdint.h"
#include "../reader_ctx.h"

struct md_string_reader_ctx {
    char *str;
    char *cur;
    char *end;
};

typedef struct md_string_reader_ctx md_string_reader_t;

md_reader_t *md_make_string_reader(char *src);

void md_free_string_reader(md_reader_t *mdStringReader);

#endif //MD_STRING_READER_H
