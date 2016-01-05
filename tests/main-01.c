/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stderr
    func  : fputs
            rewind
            tmpfile */
#include <stddef.h>
/*  type  : size_t */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE */
#include <string.h>
/*  func  : strcmp
            strlen */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include rainicorn headers */
#include <rainicorn/rainicorn.h>
/*  macro : RC_F
            RC_S
            RC_XFBS
            RC_BOLD
            RC_RED
            RC_GREEN
            RC_YELLOW */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/assert.h"
/*  macro : pr_assert
            pr_assert_x */
#include "prelude/ownership.h"
/*  type  : pr_Ownership
    macro : PR_OWNERSHIP_MAX_SPUT_LEN
    const : pr_OWNS_NONE
            pr_OWNS_ALL
            pr_OWNS_SELF
            pr_OWNS_ATTR_*
    func  : pr_Ownership_str
            pr_Ownership_put
            pr_Ownership_sput
            pr_Ownership_sput_len */

/*----------------------------------------------------------------------------*/
#define assert(EXPR)                                                           \
    pr_assert_x((EXPR), #EXPR, "=> " RC_F(RC_RED, "FAIL") RC_XFBS(""))
#define test(PREFIX, MESSAGE, FUNCTION)                                        \
    fputs(PREFIX RC_S(RC_BOLD, MESSAGE) RC_XFBS(" "), stderr);                 \
    FUNCTION;                                                                  \
    fputs("=> " RC_F(RC_GREEN, "PASS") RC_XFBS("\n"), stderr)


/*----------------------------------------------------------------------------*/
/* Global constants */
static const pr_Ownership INVALID = (pr_Ownership)(1u << 16);
static const char *const SPUT_OUT[] =
{
    "<pr_Ownership pr_OWNS_NONE>",
    "<pr_Ownership pr_OWNS_ALL>",
    "<pr_Ownership pr_OWNS_SELF>",
    "<pr_Ownership pr_OWNS_ATTR_15>",
    "<pr_Ownership pr_OWNS_SELF|pr_OWNS_ATTR_9|pr_OWNS_ATTR_15>",
    "<pr_Ownership pr_OWNS_SELF|pr_OWNS_ATTR_1|pr_OWNS_ATTR_2|pr_OWNS_ATTR_3|"
                  "pr_OWNS_ATTR_4|pr_OWNS_ATTR_5|pr_OWNS_ATTR_6|pr_OWNS_ATTR_7|"
                  "pr_OWNS_ATTR_8|pr_OWNS_ATTR_9|pr_OWNS_ATTR_10|"
                  "pr_OWNS_ATTR_11|pr_OWNS_ATTR_12|pr_OWNS_ATTR_13|"
                  "pr_OWNS_ATTR_14|pr_OWNS_ATTR_15>",
    "<pr_Ownership (UNKNOWN)>",
};


/*----------------------------------------------------------------------------*/
/* Global variables */
static size_t        length;
static FILE         *tmpout;
static pr_Ownership  OWNS_FEW,
                     OWNS_LOT;
static char         *buffer_d,
                     buffer_s[PR_OWNERSHIP_MAX_SPUT_LEN];



/*----------------------------------------------------------------------------*/
static inline void
bit_masking(void)
{
    assert(!(pr_OWNS_NONE & pr_OWNS_SELF));
    assert(pr_OWNS_ALL & pr_OWNS_SELF);
    assert(OWNS_FEW & pr_OWNS_SELF);
    assert(OWNS_FEW & pr_OWNS_ATTR_9);
    assert(OWNS_FEW & pr_OWNS_ATTR_15);
    assert(OWNS_LOT & OWNS_FEW);
}



/*----------------------------------------------------------------------------*/
static inline void
const_check(void)
{
    assert(PR_OWNERSHIP_MAX_SPUT_LEN == pr_Ownership_sput_len(OWNS_LOT));
}



/*----------------------------------------------------------------------------*/
static inline void
str_repr(void)
{
    assert(!strcmp(pr_Ownership_str(pr_OWNS_NONE)   , "pr_OWNS_NONE"));
    assert(!strcmp(pr_Ownership_str(pr_OWNS_ALL)    , "pr_OWNS_ALL"));
    assert(!strcmp(pr_Ownership_str(pr_OWNS_SELF)   , "pr_OWNS_SELF"));
    assert(!strcmp(pr_Ownership_str(pr_OWNS_ATTR_9) , "pr_OWNS_ATTR_9"));
    assert(!strcmp(pr_Ownership_str(pr_OWNS_ATTR_15), "pr_OWNS_ATTR_15"));
    assert(!strcmp(pr_Ownership_str(OWNS_FEW)       , "pr_OWNS_SELF"));
    assert(!strcmp(pr_Ownership_str(OWNS_LOT)       , "pr_OWNS_SELF"));
    /* If pr_Ownership can hold exactly 2^16 - 1 values, then INVALID is the
       pr_OWNS_NONE as, however if pr_Ownership is greater, then INVALID will
       not match any known constants */
    assert(!strcmp(pr_Ownership_str(INVALID)        , "pr_OWNS_NONE") ||
           !strcmp(pr_Ownership_str(INVALID)        , "(UNKNOWN)"));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_len(void)
{
    assert(pr_Ownership_sput_len(pr_OWNS_NONE)    == strlen(SPUT_OUT[0]) + 1);
    assert(pr_Ownership_sput_len(pr_OWNS_ALL)     == strlen(SPUT_OUT[1]) + 1);
    assert(pr_Ownership_sput_len(pr_OWNS_SELF)    == strlen(SPUT_OUT[2]) + 1);
    assert(pr_Ownership_sput_len(pr_OWNS_ATTR_15) == strlen(SPUT_OUT[3]) + 1);
    assert(pr_Ownership_sput_len(OWNS_FEW)        == strlen(SPUT_OUT[4]) + 1);
    assert(pr_Ownership_sput_len(OWNS_LOT)        == strlen(SPUT_OUT[5]) + 1);
    /* If pr_Ownership can hold exactly 2^16 - 1 values, then INVALID is the
       pr_OWNS_NONE as, however if pr_Ownership is greater, then INVALID will
       not match any known constants */
    assert((pr_Ownership_sput_len(INVALID)        == strlen(SPUT_OUT[0]) + 1) ||
           (pr_Ownership_sput_len(INVALID)        == strlen(SPUT_OUT[6]) + 1));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_out(void)
{
    length = pr_Ownership_fput(pr_OWNS_NONE, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[0]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(pr_OWNS_ALL, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[1]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(pr_OWNS_SELF, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[2]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(pr_OWNS_ATTR_15, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[3]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(OWNS_FEW, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[4]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(OWNS_LOT, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[5]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Ownership_fput(INVALID, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[6]) ||
           !strcmp(buffer_d, SPUT_OUT[0]));
    free(buffer_d);

    assert(!pr_Ownership_fput(INVALID, NULL));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_sbuff(void)
{
    pr_Ownership_sput(pr_OWNS_NONE, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[0]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(pr_OWNS_NONE) - 1);

    pr_Ownership_sput(pr_OWNS_ALL, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[1]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(pr_OWNS_ALL) - 1);

    pr_Ownership_sput(pr_OWNS_SELF, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[2]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(pr_OWNS_SELF) - 1);

    pr_Ownership_sput(pr_OWNS_ATTR_15, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[3]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(pr_OWNS_ATTR_15) - 1);

    pr_Ownership_sput(OWNS_FEW, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[4]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(OWNS_FEW) - 1);

    pr_Ownership_sput(OWNS_LOT, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[5]));
    assert(strlen(buffer_s) == pr_Ownership_sput_len(OWNS_LOT) - 1);

    /* If pr_Ownership can hold exactly 2^16 - 1 values, then INVALID is the
       pr_OWNS_NONE as, however if pr_Ownership is greater, then INVALID will
       not match any known constants */
    pr_Ownership_sput(INVALID, PR_OWNERSHIP_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[6]) ||
           !strcmp(buffer_s, SPUT_OUT[0]));
    assert((strlen(buffer_s) == pr_Ownership_sput_len(INVALID) - 1) ||
           (strlen(buffer_s) == pr_Ownership_sput_len(INVALID) - 1));

    assert(!pr_Ownership_sput(INVALID, 0, buffer_s));
    assert(!pr_Ownership_sput(INVALID, PR_OWNERSHIP_MAX_SPUT_LEN, NULL));
    pr_Ownership_sput(INVALID, 5, buffer_s);
    assert(!strcmp(buffer_s, "<pr_"));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_dbuff(void)
{
    length = pr_Ownership_sput_len(pr_OWNS_NONE);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(pr_OWNS_NONE, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[0]));
    free(buffer_d);

    length = pr_Ownership_sput_len(pr_OWNS_ALL);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(pr_OWNS_ALL, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[1]));
    free(buffer_d);

    length = pr_Ownership_sput_len(pr_OWNS_SELF);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(pr_OWNS_SELF, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[2]));
    free(buffer_d);

    length = pr_Ownership_sput_len(pr_OWNS_ATTR_15);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(pr_OWNS_ATTR_15, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[3]));
    free(buffer_d);

    length = pr_Ownership_sput_len(OWNS_FEW);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(OWNS_FEW, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[4]));
    free(buffer_d);

    length = pr_Ownership_sput_len(OWNS_LOT);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(OWNS_LOT, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[5]));
    free(buffer_d);

    /* If pr_Ownership can hold exactly 2^16 - 1 values, then INVALID is the
       pr_OWNS_NONE as, however if pr_Ownership is greater, then INVALID will
       not match any known constants */
    length = pr_Ownership_sput_len(INVALID);
    assert((buffer_d = malloc(length)));
    pr_Ownership_sput(INVALID, length, buffer_d);
    assert(!strcmp(buffer_d, SPUT_OUT[6]) ||
           !strcmp(buffer_d, SPUT_OUT[0]));
    free(buffer_d);
}



/*----------------------------------------------------------------------------*/
int
main(void)
{
    /* Set global values */
    OWNS_FEW = pr_OWNS_SELF | pr_OWNS_ATTR_9 | pr_OWNS_ATTR_15;
    OWNS_LOT = pr_OWNS_SELF    | pr_OWNS_ATTR_1  | pr_OWNS_ATTR_2  |
               pr_OWNS_ATTR_3  | pr_OWNS_ATTR_4  | pr_OWNS_ATTR_5  |
               pr_OWNS_ATTR_6  | pr_OWNS_ATTR_7  | pr_OWNS_ATTR_8  |
               pr_OWNS_ATTR_9  | pr_OWNS_ATTR_10 | pr_OWNS_ATTR_11 |
               pr_OWNS_ATTR_12 | pr_OWNS_ATTR_13 | pr_OWNS_ATTR_14 |
               pr_OWNS_ATTR_15;

    /* Start testing */
    fputs("\n"
          RC_F(RC_YELLOW, ">>>>> PRELUDE/OWNERSHIP: TESTS <<<<<")
          RC_XFBS("\n"), stderr);

    /* Open a temporary file, to use it as a file-stream */
    pr_assert((tmpout = tmpfile()), "Cannot create temporary output stream");

    /* Run test-cases */
    test("[ 1] Test: ", "bit-masking value", bit_masking());
    test("[ 2] Test: ", "constant value check", const_check());
    test("[ 3] Test: ", "string representation of value", str_repr());
    test("[ 4] Test: ", "qualified string representation length", qual_str_len());
    test("[ 5] Test: ", "printing to file-stream ", qual_str_out());
    test("[ 6] Test: ", "printing to static buffer ", qual_str_sbuff());
    test("[ 7] Test: ", "printing to dynamic buffer ", qual_str_dbuff());

    /* Clean up */
    fclose(tmpout);
    fputs("\n", stderr);
    return EXIT_SUCCESS;
}
