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


int md_string_reader_read(md_reader_t *ctx, wchar_t *buf, uint32_t length) {
    if (ctx->is_eof(ctx)) {
        return EOF;
    }

    md_string_reader_t *stringReader = ctx->data;

    int toRead = MIN(length, stringReader->length - stringReader->cur_index);

    memcpy(buf, &stringReader->str[stringReader->cur_index], toRead * sizeof(wchar_t));

    stringReader->cur_index += toRead;

    return toRead;
}

wchar_t md_string_reader_readch(md_reader_t *ctx) {
    if (ctx->is_eof(ctx)) {
        return EOF;
    }

    md_string_reader_t *stringReader = ctx->data;

    return stringReader->str[stringReader->cur_index++];
}

wchar_t md_string_reader_peekch(md_reader_t *ctx) {
    md_string_reader_t *stringReader = ctx->data;

    if (stringReader->cur_index + 1 == stringReader->length) {
        return EOF;
    }

    return stringReader->str[stringReader->cur_index + 1];
}

bool md_string_reader_is_eof(md_reader_t *ctx) {

    md_string_reader_t *stringReader = ctx->data;

    return stringReader->cur_index == stringReader->length;
}

md_reader_t *md_make_string_reader(char *src) {
    md_reader_t *reader;
    md_string_reader_t *stringReader;
    wchar_t *convertedString;
    unsigned long srclen;

    srclen = strlen(src) + 1; // account for null terminator
    reader = calloc(1, sizeof(md_reader_t));
    stringReader = calloc(1, sizeof(md_string_reader_t));
    convertedString = calloc(srclen, sizeof(wchar_t));

    if (reader == NULL && stringReader == NULL || convertedString == NULL) {
        perror("Failed to allocate string reader_ctx");
        exit(1);
    }

    mbstowcs(convertedString, src, srclen);

    stringReader->str = convertedString;
    stringReader->cur_index = 0;
    stringReader->length = wcslen(convertedString);

    reader->data = stringReader;
    reader->read = md_string_reader_read;
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
