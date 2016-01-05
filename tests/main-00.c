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
#include <jemalloc/jemalloc.h>
/*  func  : malloc
            free */

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
#include "prelude/order.h"
/*  type  : pr_Order
    macro : PR_ORDER_MAX_SPUT_LEN
    const : pr_EQUAL
            pr_NOT_EQUAL
            pr_GREATER
            pr_LESSER
            pr_UNCOMPARABLE
            pr_UNCOMPARABLE_LEFT
            pr_UNCOMPARABLE_RIGHT
    func  : pr_Order_not
            pr_Order_str
            pr_Order_put
            pr_Order_sput
            pr_Order_sput_len */

/*----------------------------------------------------------------------------*/
#define assert(EXPR)                                                           \
    pr_assert_x((EXPR), #EXPR, "=> " RC_F(RC_RED, "FAIL") RC_XFBS(""))
#define test(PREFIX, MESSAGE, FUNCTION)                                        \
    fputs(PREFIX RC_S(RC_BOLD, MESSAGE) RC_XFBS(" "), stderr);                 \
    FUNCTION;                                                                  \
    fputs("=> " RC_F(RC_GREEN, "PASS") RC_XFBS("\n"), stderr)


/*----------------------------------------------------------------------------*/
/* Global constants */
static const pr_Order    INVALID    = (pr_Order)128;
static const char *const SPUT_OUT[] =
{
    "<pr_Order pr_EQUAL>",
    "<pr_Order pr_UNCOMPARABLE_RIGHT>",
    "<pr_Order (UNKNOWN)>",
};

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Global variables */
static pr_Order    order;
static FILE       *tmpout;
static size_t      length;
static const char *pointer;
static char       *buffer_d,
                   buffer_s[PR_ORDER_MAX_SPUT_LEN];



/*----------------------------------------------------------------------------*/
static inline void
negate_vals(void)
{
    assert(pr_Order_not(pr_EQUAL)              == pr_NOT_EQUAL);
    assert(pr_Order_not(pr_NOT_EQUAL)          == pr_EQUAL);
    assert(pr_Order_not(pr_GREATER)            == pr_LESSER);
    assert(pr_Order_not(pr_LESSER)             == pr_GREATER);
    assert(pr_Order_not(pr_UNCOMPARABLE)       == pr_UNCOMPARABLE);
    assert(pr_Order_not(pr_UNCOMPARABLE_LEFT)  == pr_UNCOMPARABLE_LEFT);
    assert(pr_Order_not(pr_UNCOMPARABLE_RIGHT) == pr_UNCOMPARABLE_RIGHT);
    assert(pr_Order_not(INVALID)               == INVALID);
}



/*----------------------------------------------------------------------------*/
static inline void
bit_masking(void)
{
    assert(pr_GREATER            & pr_NOT_EQUAL);
    assert(pr_LESSER             & pr_NOT_EQUAL);
    assert(pr_UNCOMPARABLE       & pr_NOT_EQUAL);
    assert(pr_UNCOMPARABLE_LEFT  & pr_NOT_EQUAL);
    assert(pr_UNCOMPARABLE_RIGHT & pr_NOT_EQUAL);
    assert(pr_UNCOMPARABLE_LEFT  & pr_UNCOMPARABLE);
    assert(pr_UNCOMPARABLE_RIGHT & pr_UNCOMPARABLE);
}



/*----------------------------------------------------------------------------*/
static inline void
str_repr(void)
{
    assert(!strcmp(pr_Order_str(pr_EQUAL)             , "pr_EQUAL"));
    assert(!strcmp(pr_Order_str(pr_UNCOMPARABLE_RIGHT), "pr_UNCOMPARABLE_RIGHT"));
    assert(!strcmp(pr_Order_str(INVALID)              , "(UNKNOWN)"));
}



/*----------------------------------------------------------------------------*/
static inline void
const_check(void)
{
    assert(PR_ORDER_MAX_SPUT_LEN == pr_Order_sput_len(pr_UNCOMPARABLE_RIGHT));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_len(void)
{
    assert(pr_Order_sput_len(pr_EQUAL)              == strlen(SPUT_OUT[0]) + 1);
    assert(pr_Order_sput_len(pr_UNCOMPARABLE_RIGHT) == strlen(SPUT_OUT[1]) + 1);
    assert(pr_Order_sput_len(INVALID)               == strlen(SPUT_OUT[2]) + 1);
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_out(void)
{
    length = pr_Order_fput(pr_EQUAL, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[0]));
    free(buffer_d);
    rewind(tmpout);

    length = pr_Order_fput(pr_UNCOMPARABLE_RIGHT, tmpout);
    assert((buffer_d = malloc(length + 1)));
    rewind(tmpout);
    assert(fgets(buffer_d, (int)length, tmpout));
    buffer_d[length] = '\0';
    assert(!strcmp(buffer_d, SPUT_OUT[1]));
    free(buffer_d);

    assert(!pr_Order_fput(INVALID, NULL));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_sbuff(void)
{
    pr_Order_sput(pr_EQUAL, PR_ORDER_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[0]));
    assert(strlen(buffer_s) == pr_Order_sput_len(pr_EQUAL) - 1);

    pr_Order_sput(pr_UNCOMPARABLE_RIGHT, PR_ORDER_MAX_SPUT_LEN, buffer_s);
    assert(!strcmp(buffer_s, SPUT_OUT[1]));
    assert(strlen(buffer_s) == pr_Order_sput_len(pr_UNCOMPARABLE_RIGHT) - 1);

    assert(!pr_Order_sput(INVALID, 0, buffer_s));
    assert(!pr_Order_sput(INVALID, PR_ORDER_MAX_SPUT_LEN, NULL));
    pr_Order_sput(INVALID, 3, buffer_s);
    assert(!strcmp(buffer_s, "<p"));
}



/*----------------------------------------------------------------------------*/
static inline void
qual_str_dbuff(void)
{
    for (order=pr_UNCOMPARABLE_RIGHT, pointer=SPUT_OUT[1];
         order;
         order=pr_EQUAL, pointer=SPUT_OUT[0])
    {
        length = pr_Order_sput_len(order);
        assert((buffer_d = malloc(length)));
        pr_Order_sput(order, length, buffer_d);
        assert(!strcmp(buffer_d, pointer));
        free(buffer_d);
    }
}



/*----------------------------------------------------------------------------*/
int
main(void)
{
    /* Start testing */
    fputs("\n"
          RC_F(RC_YELLOW, ">>>>> PRELUDE/ORDER: TESTS <<<<<")
          RC_XFBS("\n"), stderr);
    /* Open a temporary file, to use it as a file-stream */
    pr_assert((tmpout = tmpfile()), "Cannot create temporary output stream");

    /* Run test-cases */
    test("[ 1] Test: ", "negate value", negate_vals());
    test("[ 2] Test: ", "bit-masking value", bit_masking());
    test("[ 3] Test: ", "string representation of value", str_repr());
    test("[ 4] Test: ", "constant values check", const_check());
    test("[ 5] Test: ", "qualified string representation length", qual_str_len());
    test("[ 6] Test: ", "printing to file-stream ", qual_str_out());
    test("[ 7] Test: ", "printing to static buffer ", qual_str_sbuff());
    test("[ 8] Test: ", "printing to dynamic buffer ", qual_str_dbuff());

    /* Clean up */
    fclose(tmpout);
    fputs("\n", stderr);
    return EXIT_SUCCESS;
}
