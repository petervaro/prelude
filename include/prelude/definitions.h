/* INFO **
** INFO */

/* Header guard */
#ifndef PR_DEFINITIONS_H_1761445857113696
#define PR_DEFINITIONS_H_1761445857113696 1

/* Macros to define type specific `min` and `max` functions.

   NOTE: PR_DEF_*_ORDER macros requires the <prelude/order.h> header file to be
         included (because of the constants: pr_LESSER and pr_GREATER) */


/*----------------------------------------------------------------------------*/
#define PR_DEF_MIN_H(NAME, TYPE, QUAL)                                         \
    QUAL TYPE                                                                  \
    NAME(TYPE a,                                                               \
         TYPE b);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PR_DEF_MIN(NAME, TYPE, QUAL)                                           \
    QUAL TYPE                                                                  \
    NAME(TYPE a,                                                               \
         TYPE b)                                                               \
    {                                                                          \
        if (a < b)                                                             \
            return a;                                                          \
        return b;                                                              \
    }


/*----------------------------------------------------------------------------*/
#define PR_DEF_MAX_H(NAME, TYPE, QUAL)                                         \
    QUAL TYPE                                                                  \
    NAME(TYPE a,                                                               \
         TYPE b);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PR_DEF_MAX(NAME, TYPE, QUAL)                                           \
    QUAL TYPE                                                                  \
    NAME(TYPE a,                                                               \
         TYPE b)                                                               \
    {                                                                          \
        if (a > b)                                                             \
            return a;                                                          \
        return b;                                                              \
    }


/*----------------------------------------------------------------------------*/
#define PR_DEF_MIN_ORDER_H(NAME, TYPE, QUAL)                                   \
    QUAL TYPE                                                                  \
    NAME(const TYPE a,                                                         \
         const TYPE b);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PR_DEF_MIN_ORDER(NAME, TYPE, COMPARE, QUAL)                            \
    QUAL TYPE                                                                  \
    NAME(const TYPE a,                                                         \
         const TYPE b)                                                         \
    {                                                                          \
        if (COMPARE(a, b) == pr_LESSER)                                        \
            return a;                                                          \
        return b;                                                              \
    }


/*----------------------------------------------------------------------------*/
#define PR_DEF_MAX_ORDER_H(NAME, TYPE, QUAL)                                   \
    QUAL TYPE                                                                  \
    NAME(const TYPE a,                                                         \
         const TYPE b);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PR_DEF_MAX_ORDER(NAME, TYPE, COMPARE, QUAL)                            \
    QUAL TYPE                                                                  \
    NAME(const TYPE a,                                                         \
         const TYPE b)                                                         \
    {                                                                          \
        if (COMPARE(a, b) == pr_GREATER)                                       \
            return a;                                                          \
        return b;                                                              \
    }

#endif /* PR_DEFINITIONS_H_1761445857113696 */
