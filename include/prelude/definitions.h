/* INFO **
** INFO */

/* Header guard */
#ifndef PR_DEFINITIONS_H_1761445857113696
#define PR_DEFINITIONS_H_1761445857113696 1

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
