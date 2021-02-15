#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "tokenizer/tokenizer.h"
#include "reader/string_reader/string_reader.h"

#if !defined(NDEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)
#else
#define TICK(X) ;
#define TOCK(X) ;
#endif

int work() {
    const char *src = "## já vás mám rád";

    setlocale(LC_ALL, "cs_CZ.UTF-8");
    md_reader_t *readerCtx = md_make_string_reader((char *) src);

    md_token_t tok;
    while ((tok = next_tok(readerCtx)).type != EOF_TOK) {
        printtok(tok);

        freetok(tok);
    }

    printtok(tok);
    freetok(tok);

    md_free_string_reader(readerCtx);

    return 0;
}

int main() {
    int code = 0;

    TICK(A);
    code = work();
    TOCK(A);


    return code;
}
