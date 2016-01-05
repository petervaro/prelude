/* INFO **
** INFO */

/* Header guard */
#ifndef PR_ASSERT_H_8765756491050648
#define PR_ASSERT_H_8765756491050648 1

/*  Works the same way, as the standard library's assert (can be muted by
    defining NDEBUG) but it is capable of printing an additional message out.
    The message has to be a non NULL pointer. The passed message will be printed
    to the stderr file stream.

    NOTE: Using this header alone does not require to link against either
    libprelude.a or libprelude.so. */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  value : stderr
    func  : fprintf */
#include <stdlib.h>
/*  const : EXIT_FAILURE
    func  : exit */

/*----------------------------------------------------------------------------*/
#ifdef NDEBUG
    #define pr_assert(EXPRESSION, MESSAGE) ((void)0)
#else
    #define pr_assert_x(EXPRESSION, EXPRESSION_STRING, MESSAGE)                \
        for (; !(EXPRESSION); exit(EXIT_FAILURE))                              \
            fprintf(stderr, "%s\n%s%d%s%s%s\n",                                \
                    MESSAGE,                                                   \
                    __FILE__ ":",                                              \
                    __LINE__,                                                  \
                     ": ",                                                     \
                    __func__,                                                  \
                    " Assertion `" EXPRESSION_STRING "' failed.")
    #define pr_assert(EXPRESSION, MESSAGE)                                     \
        pr_assert_x(EXPRESSION, #EXPRESSION, MESSAGE)
#endif /* NDEBUG */

#endif /* PR_ASSERT_H_8765756491050648 */
