//
// Created by falta on 2/13/2021.
//

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "wchar.h"
#include "stdio.h"

#define CUR_BUF_LEN 1024

#define IS_H1(buf, next) buf[0] == '#' && next != '#'
#define IS_H2(buf, next) buf[0] == '#' && buf[1] == '#' && next != '#'
#define IS_H3(buf, next) buf[0] == '#' && buf[1] == '#' && buf[2] == '#' && next != '#'
#define IS_H4(buf, next) buf[0] == '#' && buf[1] == '#' && buf[2] == '#' && buf[3] == '#' && next != '#'
#define IS_H5(buf, next) buf[0] == '#' && buf[1] == '#' && buf[2] == '#' && buf[3] == '#' && buf[4] == '#' && next != '#'
#define IS_H6(buf, next) buf[0] == '#' && buf[1] == '#' && buf[2] == '#' && buf[3] == '#' && buf[4] == '#' && buf[5] == '#' && next != '#'
#define IS_SPACE(buf) buf[0] == ' '
#define IS_TAB(buf) buf[0] == '\t'
#define IS_NEWLINE(buf) buf[0] == '\n' || (buf[0] == '\r' && buf[1] == '\n')
#define IS_BULLET(buf) buf[0] == '-' || buf[0] == '*'
#define IS_TERMINAL(buf, ch) ch == ' ' || ch == '\t' || ch == '\r' || (buf[0] != '\r' && ch == '\n') || ch == 0 || ch == EOF

static const md_token_t EOF_TOKEN = {EOF_TOK, NULL};


md_token_t next_tok(md_reader_t *reader) {
    utf8_int32_t buf[CUR_BUF_LEN] = {0};
    utf8_int32_t next;
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
            if (IS_H6(buf, next)) {
                tok = mktoken(H6, md_cdptostr(buf));
                break;
            }
            if (IS_H5(buf, next)) {
                tok = mktoken(H5, md_cdptostr(buf));
                break;
            }
            if (IS_H4(buf, next)) {
                tok = mktoken(H4, md_cdptostr(buf));
                break;
            }
            if (IS_H3(buf, next)) {
                tok = mktoken(H3, md_cdptostr(buf));
                break;
            }
            if (IS_H2(buf, next)) {
                tok = mktoken(H2, md_cdptostr(buf));
                break;
            }
            if (IS_H1(buf, next)) {
                tok = mktoken(H1, md_cdptostr(buf));
                break;
            }
            if (IS_NEWLINE(buf)) {
                tok = mktoken(NEWLINE, md_cdptostr(buf));
                break;
            }
            if (IS_BULLET(buf)) {
                tok = mktoken(BULLET, md_cdptostr(buf));
                break;
            }
            if (IS_SPACE(buf)) {
                tok = mktoken(WHITESPACE, md_cdptostr(buf));
                break;
            }
            if (IS_TAB(buf)) {
                tok = mktoken(TAB, md_cdptostr(buf));
                break;
            }
            if (IS_TERMINAL(buf,next)) { // tokens are terminated by space
                tok = mktoken(TEXT, md_cdptostr(buf));
                break;
            }
        }

        next = reader->peekch(reader);
        buf[i++] = reader->readch(reader);
    }

    if (tok.type == NONE) {
        if (buf[0] == 0) { // if buf empty return eof
            tok = EOF_TOKEN;
        } else { // if buf contains something, return it as text node
            tok = mktoken(TEXT, md_cdptostr(buf));
        }
    }

    return tok;
}

