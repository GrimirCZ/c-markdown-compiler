//
// Created by falta on 2/13/2021.
//

#include <stddef.h>
#include "stdlib.h"
#include "string_reader.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include "math.h"
#include "../../util.h"
#include "../../util/utf8.h"


utf8_int32_t md_string_reader_readch(md_reader_t *ctx) {
    if (ctx->is_eof(ctx)) {
        return EOF;
    }

    utf8_int32_t ret;
    md_string_reader_t *stringReader = ctx->data;

    stringReader->cur = utf8codepoint(stringReader->cur, &ret);

    return ret;
}

utf8_int32_t md_string_reader_peekch(md_reader_t *ctx) {
    md_string_reader_t *stringReader = ctx->data;

    utf8_int32_t out;

    char *nextStart = md_nextcodepoint(stringReader->cur);

    if (nextStart >= stringReader->end) {
        return EOF;
    }

    utf8codepoint(nextStart, &out);

    return out;
}

bool md_string_reader_is_eof(md_reader_t *ctx) {

    md_string_reader_t *stringReader = ctx->data;

    return stringReader->cur == stringReader->end;
}

md_reader_t *md_make_string_reader(char *src) {
    md_reader_t *reader;
    md_string_reader_t *stringReader;
    char *str;
    unsigned long len;

    len = strlen(src) + 1; // account for null terminator
    reader = calloc(1, sizeof(md_reader_t));
    stringReader = calloc(1, sizeof(md_string_reader_t));
    str = strdup(src);

    if (reader == NULL && stringReader == NULL) {
        perror("Failed to allocate string reader_ctx");
        exit(1);
    }

    stringReader->str = str;
    stringReader->cur = str;
    stringReader->end = str + len;

    reader->data = stringReader;
    reader->readch = md_string_reader_readch;
    reader->peekch = md_string_reader_peekch;
    reader->is_eof = md_string_reader_is_eof;

    return reader;
}

void md_free_string_reader(md_reader_t *reader) {
    md_string_reader_t *stringReader = (md_string_reader_t *) reader->data;

    free(stringReader->str);
    free(stringReader);
    free(reader);
}
