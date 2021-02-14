#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "wchar.h"
#include "stdlib.h"
#include "tokenizer/tokenizer.h"
#include "reader/reader_ctx.h"
#include "reader/string_reader/string_reader.h"

int main() {
    const char *src = "# já vás mám rád";

    setlocale(LC_ALL, "cs_CZ.UTF-8");
    md_reader_t *readerCtx = md_make_string_reader((char *) src);

    md_token_t tok;
    while ((tok = next_tok(readerCtx)).type != EOF_TOK) {
        switch (tok.type) {
            case H1:
                printf("H1\n");
                break;
            case H2:
                printf("H2\n");
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
        }

        freetok(tok);
    }

    md_free_string_reader(readerCtx);

    return 0;
}
