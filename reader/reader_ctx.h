//
// Created by falta on 2/13/2021.
//


#ifndef MD_READER_CTX_H
#define MD_READER_CTX_H

#include <stddef.h>
#include <stdbool.h>
#include "stdint.h"
#include "../util/utf8.h"

typedef struct md_reader md_reader_t;

typedef int (*md_read)(md_reader_t *, char *, uint32_t);

typedef utf8_int32_t (*md_readch)(md_reader_t *);

typedef bool (*md_is_eof)(md_reader_t *);

struct md_reader {
    void *data;

    md_readch readch; // read char and increment counter
    md_readch peekch; // return next char without incrementing
    md_is_eof is_eof; // has reached end of stream
};


#endif //MD_READER_CTX_H
