//
// Created by falta on 2/14/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "token.h"

#define MD_IS_UNIX_LINE_ENDINGS(txt) txt[0] == '\n'

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
            printf("H3\n");
            break;
        case H4:
            printf("H4\n");
            break;
        case H5:
            printf("H5\n");
            break;
        case H6:
            printf("H6\n");
            break;
        case TEXT:
            printf("TEXT(\"%s\")\n", tok.text);
            break;
        case WHITESPACE:
            printf("WHITESPACE\n");
            break;
        case NEWLINE:
            printf("NEWLINE(%s)\n", MD_IS_UNIX_LINE_ENDINGS(tok.text) ? "Unix" : "Windows");
            break;
        case TAB:
            printf("TAB\n");
            break;
        case BULLET:
            printf("BULLET\n");
            break;
        case EOF_TOK:
            printf("EOF\n");
            break;
        case NONE:
            printf("EMPTY_TOKEN\n");
            break;
        default:
            printf("Unknown token");
    }
}