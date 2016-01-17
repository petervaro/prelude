/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stdout
    func  : ftell
            fputs
            fputc */
#include <stddef.h>
/*  type  : size_t */
#include <string.h>
/*  func  : memcpy
            strlen */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/order.h"
/*  type  : pr_Order */
#include "prelude/definitions.h"
/*  macro : PR_DEF_MIN */


/*----------------------------------------------------------------------------*/
/* Define function */
PR_DEF_MIN(min, size_t, static inline)

/*----------------------------------------------------------------------------*/
/* Module level constants */
#define PR_PREFIX   "<pr_Order "
#define PR_SUFFIX_S ">"
#define PR_SUFFIX_C '>'
static const char *const pr_ORDERS[] =
{
    "pr_EQUAL",
    "pr_NOT_EQUAL",
    "pr_GREATER",
    "pr_LESSER",
    "pr_UNCOMPARABLE",
    "pr_UNCOMPARABLE_LEFT",
    "pr_UNCOMPARABLE_RIGHT",
    "(UNKNOWN)",
};


/*----------------------------------------------------------------------------*/
/* Public constants */
const pr_Order pr_EQUAL              = (pr_Order)0,  /* 00000000 */
               pr_NOT_EQUAL          = (pr_Order)1,  /* 00000001 */
               pr_GREATER            = (pr_Order)3,  /* 00000011 */
               pr_LESSER             = (pr_Order)5,  /* 00000101 */
               pr_UNCOMPARABLE       = (pr_Order)9,  /* 00001001 */
               pr_UNCOMPARABLE_LEFT  = (pr_Order)25, /* 00011001 */
               pr_UNCOMPARABLE_RIGHT = (pr_Order)41; /* 00101001 */



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
const char*
pr_Order_str(pr_Order self)
{
    /* Return string representation */
         if (self == pr_EQUAL)              return pr_ORDERS[0];
    else if (self == pr_NOT_EQUAL)          return pr_ORDERS[1];
    else if (self == pr_GREATER)            return pr_ORDERS[2];
    else if (self == pr_LESSER)             return pr_ORDERS[3];
    else if (self == pr_UNCOMPARABLE)       return pr_ORDERS[4];
    else if (self == pr_UNCOMPARABLE_LEFT)  return pr_ORDERS[5];
    else if (self == pr_UNCOMPARABLE_RIGHT) return pr_ORDERS[6];
    else                                    return pr_ORDERS[7];
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Order_fput(pr_Order  self,
              FILE     *stream)
{
    /* If stream is NULL */
    if (!stream)
        return 0;

    /* Print qualified representation */
    fputs(PR_PREFIX, stream);
    fputs(pr_Order_str(self), stream);
    fputc(PR_SUFFIX_C, stream);

    /* Return the number of bytes that has been written to stream */
    return pr_Order_sput_len(self);
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Order_put(pr_Order self)
{
    return pr_Order_fput(self, stdout);
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Order_sput(pr_Order  self,
              size_t    length,
              char     *buffer)
{
    /* Local variables */
    size_t start,
           required;

    /* If length is 0 or buffer is NULL */
    if (!length ||
        !buffer)
            return 0;

    /* Wrire prefix to buffer */
    start = --length;
    required = min(length, (sizeof PR_PREFIX) - 1);
    memcpy(buffer, PR_PREFIX, required);
    buffer += required;
    length -= required;

    /* Write order to buffer */
    required = min(length, strlen(pr_Order_str(self)));
    memcpy(buffer, pr_Order_str(self), required);
    buffer += required;
    length -= required;

    /* Write suffix to buffer */
    required = min(length, (sizeof PR_SUFFIX_S) - 1);
    memcpy(buffer, PR_SUFFIX_S, required);
    buffer += required;

    /* Null-terminate buffer */
    buffer[0] = '\0';

    /* Return the number of bytes that has been written to stream */
    return start - length;
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Order_sput_len(pr_Order self)
{
    return (sizeof PR_PREFIX PR_SUFFIX_S) + strlen(pr_Order_str(self));
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
pr_Order
pr_Order_not(pr_Order self)
{
    /* Negate self */
         if (self == pr_EQUAL)     return pr_NOT_EQUAL;
    else if (self == pr_NOT_EQUAL) return pr_EQUAL;
    else if (self == pr_GREATER)   return pr_LESSER;
    else if (self == pr_LESSER)    return pr_GREATER;
    else                            return self;
}

#undef PR_SUFFIX_C
#undef PR_SUFFIX_S
#undef PR_PREFIX
