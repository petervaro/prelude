/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stderr
    func  : fputs */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE */

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
#include "prelude/order.h"
/*  type  : pr_Order
    const : pr_EQUAL
            pr_LESSER
            pr_GREATER */
#include "prelude/assert.h"
/*  macro : pr_assert_x */
#include "prelude/definitions.h"
/*  type  : pr_Pointer
    macro : PR_DEF_MIN
            PR_DEF_MAX
            PR_DEF_MIN_H
            PR_DEF_MAX_H
            PR_DEF_MIN_ORDER
            PR_DEF_MAX_ORDER */

/*----------------------------------------------------------------------------*/
#define assert(EXPR)                                                           \
    pr_assert_x((EXPR), #EXPR, "=> " RC_F(RC_RED, "FAIL") RC_XFBS(""))
#define test(PREFIX, MESSAGE, FUNCTION)                                        \
    fputs(PREFIX RC_S(RC_BOLD, MESSAGE) RC_XFBS(" "), stderr);                 \
    FUNCTION;                                                                  \
    fputs("=> " RC_F(RC_GREEN, "PASS") RC_XFBS("\n"), stderr)


/*----------------------------------------------------------------------------*/
typedef int Int;

static inline pr_Order
Int_cmp(Int a,
        Int b)
{
    if (a == b)
        return pr_EQUAL;
    else if (a < b)
        return pr_LESSER;
    else
        return pr_GREATER;
}

PR_DEF_MIN_H(int_min, int,)
PR_DEF_MAX_H(int_max, int,)
PR_DEF_MIN_ORDER(Int_min, Int, Int_cmp, static)
PR_DEF_MAX_ORDER(Int_max, Int, Int_cmp, static)

/*----------------------------------------------------------------------------*/
static inline void
min_scalar(void)
{
    assert(int_min(12, -9) == -9);
}

/*----------------------------------------------------------------------------*/
static inline void
max_scalar(void)
{
    assert(int_max(12, -19) == 12);
}

/*----------------------------------------------------------------------------*/
static inline void
min_order(void)
{
    assert(Int_min(12, -9) == -9);
}

/*----------------------------------------------------------------------------*/
static inline void
max_order(void)
{
    assert(Int_max(12, -9) == 12);
}

/*----------------------------------------------------------------------------*/
int
main(void)
{
    /* Start testing */
    fputs("\n"
          RC_F(RC_YELLOW, ">>>>> PRELUDE/DEFINITIONS: TESTS <<<<<")
          RC_XFBS("\n"), stderr);

    /* Run tests */
    test("[ 1] Test: ", "min() on scalar (int)", min_scalar());
    test("[ 2] Test: ", "max() on scalar (int)", max_scalar());
    test("[ 3] Test: ", "min() on orderable (Int)", min_order());
    test("[ 4] Test: ", "max() on orderable (Int)", max_order());

    /* Finish testing */
    fputs("\n", stderr);
    return EXIT_SUCCESS;
}

PR_DEF_MIN(int_min, int,)
PR_DEF_MAX(int_max, int,)
