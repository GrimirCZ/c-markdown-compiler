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
                wprintf(L"H1\n");
                break;
            case H2:
                wprintf(L"H2\n");
                break;
            case TEXT:
                wprintf(L"TEXT(\"%S\")\n", tok.text);
                break;
            case WHITESPACE:
                wprintf(L"WHITESPACE\n");
                break;
            case EOF_TOK:
                wprintf(L"EOF\n");
                break;
        }

        freetok(tok);
    }

    md_free_string_reader(readerCtx);

    return 0;
}
