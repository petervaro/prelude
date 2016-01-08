/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stdout
    func  : snprintf
            fputs */
#include <stddef.h>
/*  type  : size_t
    const : NULL */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/order.h"
/*  type  : pr_Order
    const : pr_EQUAL
            pr_NOT_EQUAL
            pr_UNCOMPARABLE
            pr_UNCOMPARABLE_LEFT
            pr_UNCOMPARABLE_RIGHT */
#include "prelude/pointer.h"
/*  type  : pr_Pointer
    const : pr_Pointer_NONE
            pr_Pointer_DATA
            pr_Pointer_FUNC */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PR_PREFIX      "<pr_Pointer "
#define PR_TYPE_PREFIX PR_PREFIX "{.type="
#define PR_DATA_INFIX  ", .data="
#define PR_FUNC_INFIX  ", .func="
#define PR_TYPE_SUFFIX "}" PR_SUFFIX
#define PR_SUFFIX      ">"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Compatibility helper macros */
#define PR_GET_TYPE(SELF)        ((SELF)->type)
#define PR_SET_TYPE(SELF, VALUE) ((SELF)->type = VALUE)
#if __STDC_VERSION__ >= 201112L
    #define PR_GET(SELF, MEMBER)        ((SELF)->MEMBER)
    #define PR_SET(SELF, MEMBER, VALUE) ((SELF)->MEMBER = VALUE)
#else
    #define PR_GET(SELF, MEMBER)        ((SELF)->value.MEMBER)
    #define PR_SET(SELF, MEMBER, VALUE) ((SELF)->value.MEMBER = VALUE)
#endif

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static const char *const TYPE_STR[] =
{
    "pr_Pointer_NONE",
    "pr_Pointer_DATA",
    "pr_Pointer_FUNC",
    "(UNKNOWN)",
};
static const char *const STATIC_STR[] =
{
    PR_PREFIX "pr_Pointer_NONE" PR_SUFFIX,
    PR_PREFIX "pr_Pointer_DATA" PR_SUFFIX,
    PR_PREFIX "pr_Pointer_FUNC" PR_SUFFIX,
    PR_PREFIX "(UNKNOWN)"       PR_SUFFIX,
};



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
const char*
pr_Pointer_str(const pr_Pointer *self)
{
    #ifndef PR_FAST
        /* If self is NULL */
        if (!self)
            return NULL;
    #endif

    switch (PR_GET_TYPE(self))
    {
        case pr_Pointer_NONE : return STATIC_STR[0];
        case pr_Pointer_DATA : return STATIC_STR[1];
        case pr_Pointer_FUNC : return STATIC_STR[2];
        default              : return STATIC_STR[3];
    }
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_fput(const pr_Pointer *self,
                FILE             *stream)
{
    int result;

    #ifndef PR_FAST
        /* If stream is NULL */
        if (!stream)
            return (size_t)0;
        /* If self is NULL */
        else if (!self)
        {
            fputs(PR_PREFIX "(NULL)" PR_SUFFIX, stream);
            return (sizeof PR_PREFIX "(NULL)" PR_SUFFIX) - 1;
        }
    #endif

    /* TODO: replace fprintf with pp_Pointer_fput() and
             pp_FuncPointer_fput() */
    switch (PR_GET_TYPE(self))
    {
        case pr_Pointer_NONE:
            fputs(PR_TYPE_PREFIX "pr_Pointer_NONE" PR_TYPE_SUFFIX, stream);
            return (sizeof PR_TYPE_PREFIX "pr_Pointer_NONE" PR_TYPE_SUFFIX) - 1;

        case pr_Pointer_DATA:
            result = fprintf(stream, PR_TYPE_PREFIX "pr_Pointer_DATA"
                             PR_DATA_INFIX "%p" PR_TYPE_SUFFIX,
                             PR_GET(self, data));
            return result > 0 ? (size_t)result : (size_t)0;

        case pr_Pointer_FUNC:
            fputs(PR_TYPE_PREFIX "pr_Pointer_FUNC"
                  PR_FUNC_INFIX "(function)" PR_TYPE_SUFFIX, stream);
            return (sizeof PR_TYPE_PREFIX "pr_Pointer_FUNC"
                           PR_FUNC_INFIX "(function)" PR_TYPE_SUFFIX) - 1;

        default:
            fputs(PR_TYPE_PREFIX "(UNKNOWN)" PR_TYPE_SUFFIX, stream);
            return (sizeof PR_TYPE_PREFIX "(UNKNOWN)" PR_TYPE_SUFFIX) - 1;
    }
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_sput(const pr_Pointer *self,
                size_t            length,
                char             *buffer)
{
    #ifndef PR_FAST
        /* If length is 0 or buffer is NULL */
        if (!length ||
            !buffer)
                return (size_t)0;
        /* If self is NULL */
        else if (!self)
            return (size_t)snprintf(buffer,
                                    length,
                                    PR_PREFIX "(NULL)" PR_SUFFIX);
    #endif

    /* TODO: replace fprintf with pp_Pointer_fput() and
             pp_FuncPointer_fput() */
    switch (PR_GET_TYPE(self))
    {
        case pr_Pointer_NONE:
            return (size_t)snprintf(buffer,
                                    length,
                                    PR_TYPE_PREFIX "pr_Pointer_NONE"
                                        PR_TYPE_SUFFIX);

        case pr_Pointer_DATA:
            return (size_t)snprintf(buffer,
                                    length,
                                    PR_TYPE_PREFIX "pr_Pointer_DATA"
                                        PR_DATA_INFIX "%p" PR_TYPE_SUFFIX,
                                    PR_GET(self, data));

        case pr_Pointer_FUNC:
            return (size_t)snprintf(buffer,
                                    length,
                                    PR_TYPE_PREFIX "pr_Pointer_FUNC"
                                        PR_FUNC_INFIX "(function)"
                                        PR_TYPE_SUFFIX);

        default:
            return (size_t)snprintf(buffer,
                                    length,
                                    PR_TYPE_PREFIX "(UNKNOWN)" PR_TYPE_SUFFIX);
    }
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_sput_len(const pr_Pointer *self)
{
    if (!self)
        return sizeof PR_PREFIX "(NULL)" PR_SUFFIX;

    /* TODO: replace snprintf with pp_Pointer_sput_len() and
             pp_FuncPointer_sput_len() */
    switch (PR_GET_TYPE(self))
    {
        case pr_Pointer_NONE:
            return sizeof PR_TYPE_PREFIX "pr_Pointer_NONE" PR_TYPE_SUFFIX;

        case pr_Pointer_DATA:
            return (size_t)snprintf(NULL, 0,
                                    PR_TYPE_PREFIX "pr_Pointer_DATA"
                                    PR_DATA_INFIX "%p" PR_TYPE_SUFFIX,
                                    PR_GET(self, data));

        case pr_Pointer_FUNC:
            return sizeof PR_TYPE_PREFIX "pr_Pointer_FUNC"
                          PR_FUNC_INFIX "(function)" PR_TYPE_SUFFIX;

        default:
            return sizeof PR_TYPE_PREFIX "(UNKNOWN)" PR_TYPE_SUFFIX;
    }
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
pr_Order
pr_Pointer_cmp(const pr_Pointer *self,
               const pr_Pointer *other)
{
    if (!self)
        return pr_UNCOMPARABLE_LEFT;
    else if (!other)
        return pr_UNCOMPARABLE_RIGHT;
    else if (PR_GET_TYPE(self) != PR_GET_TYPE(other))
        return pr_UNCOMPARABLE;

    switch (PR_GET_TYPE(self))
    {
        case pr_Pointer_NONE:
            return pr_EQUAL;

        case pr_Pointer_DATA:
            return PR_GET(self, data) == PR_GET(other, data) ? pr_EQUAL
                                                             : pr_NOT_EQUAL;
        case pr_Pointer_FUNC:
            return PR_GET(self, func) == PR_GET(other, func) ? pr_EQUAL
                                                             : pr_NOT_EQUAL;
        default:
            return pr_UNCOMPARABLE;
    }
}

#undef PR_SET
#undef PR_GET
#undef PR_SET_TYPE
#undef PR_GET_TYPE
#undef PR_SUFFIX
#undef PR_TYPE_SUFFIX
#undef PR_FUNC_INFIX
#undef PR_DATA_INFIX
#undef PR_TYPE_PREFIX
#undef PR_PREFIX
