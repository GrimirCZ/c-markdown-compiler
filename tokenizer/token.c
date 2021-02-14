//
// Created by falta on 2/14/2021.
//

#include <stdlib.h>
#include "token.h"

md_token_t mktoken(md_token_type_t tp, wchar_t *txt) {
    return (md_token_t) {.type=tp, .text=txt, .data=NULL};
}

md_token_t mktokend(md_token_type_t tp, wchar_t *txt, void *d) {
    return (md_token_t) {.type=tp, .text=txt, .data=d};
}

void freetok(md_token_t t) {
    free(t.text);
    if (t.data != NULL) {
        free(t.data);
    }
}