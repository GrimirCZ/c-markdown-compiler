//
// Created by falta on 2/13/2021.
//

#ifndef MD_TOKEN_H
#define MD_TOKEN_H

enum md_token_type {
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    WHITESPACE,
    TAB,
    TEXT,
    BULLET,
    EOF_TOK,
    NONE
};

typedef enum md_token_type md_token_type_t;

struct md_token {
    md_token_type_t type;
    char *text;
    void *data;
};

typedef struct md_token md_token_t;

// Make token
md_token_t mktoken(md_token_type_t, char *);

// Make token with data
md_token_t mktokend(md_token_type_t, char *, void *);

void freetok(md_token_t);

void printtok(md_token_t);

#endif //MD_TOKEN_H
