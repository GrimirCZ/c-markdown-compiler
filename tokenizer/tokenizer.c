//
// Created by falta on 2/13/2021.
//

#include <stdlib.h>
#include "tokenizer.h"
#include "wchar.h"
#include "stdio.h"

#define IS_H1(buf, next) buf[0] == '#' && next != '#'
#define IS_H2(buf, next) buf[0] == '#' && buf[1] == '#' && next != '#'
#define IS_SPACE(buf) buf[0] == ' '
#define IS_TERMINAL(ch) ch == ' ' || ch == '\n' || ch == '\t' || ch == 0 || ch == EOF

static const md_token_t EOF_TOKEN = {EOF_TOK, NULL};

md_token_t next_tok(md_reader_t *reader) {
    wchar_t buf[1024] = {0};
    wchar_t next;
    int i;
    md_token_t tok;

    i = 0;
    next = 0;
    tok = (md_token_t) {NONE};

    if (reader->is_eof(reader)) {
        return EOF_TOKEN;
    }

    while (!reader->is_eof(reader)) {
        if (i != 0) { // if first round, buffer is empty
            if (IS_H2(buf, next)) {
                tok = mktoken(H1, wcsdup(buf));
                break;
            }
            if (IS_H1(buf, next)) {
                tok = mktoken(H1, wcsdup(buf));
                break;
            }
            if (IS_SPACE(buf)) {
                tok = mktoken(WHITESPACE, wcsdup(buf));
                break;
            }
            if (IS_TERMINAL(next)) { // tokens are terminated by space
                tok = mktoken(TEXT, wcsdup(buf));
                break;
            }
        }

        next = reader->peekch(reader);
        buf[i++] = reader->readch(reader);
    }

    if (tok.type == NONE && i > 0) {
        tok = mktoken(TEXT, wcsdup(buf));
    }

    return tok;
}