//
// Created by falta on 2/14/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "token.h"

md_token_t mktoken(md_token_type_t tp, char *txt) {
    return (md_token_t) {.type=tp, .text=txt, .data=NULL};
}

md_token_t mktokend(md_token_type_t tp, char *txt, void *d) {
    return (md_token_t) {.type=tp, .text=txt, .data=d};
}

void freetok(md_token_t t) {
    free(t.text);
    if (t.data != NULL) {
        free(t.data);
    }
}

void printtok(md_token_t tok) {
    switch (tok.type) {

        case H1:
            printf("H1\n");
            break;
        case H2:
            printf("H2\n");
            break;
        case H3:
            break;
        case H4:
            break;
        case H5:
            break;
        case H6:
            break;
        case TEXT:
            printf("TEXT(\"%s\")\n", tok.text);
            break;
        case WHITESPACE:
            printf("WHITESPACE\n");
            break;
        case EOF_TOK:
            printf("EOF\n");
            break;
        case TAB:
            break;
        case BULLET:
            break;
        case NONE:
            break;
    }
}