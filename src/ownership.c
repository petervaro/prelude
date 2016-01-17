/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stdout
    func  : fputc
            fputs */
#include <stddef.h>
/*  type  : size_t */
#include <stdbool.h>
/*  macro : bool
    const : true
            false */
#include <string.h>
/*  func  : memcpy
            strlen */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/ownership.h"
/*  type  : pr_Ownership */
#include "prelude/definitions.h"
/*  macro : PR_DEF_MIN */


/*----------------------------------------------------------------------------*/
/* Define function */
PR_DEF_MIN(min, size_t, static inline)


/*----------------------------------------------------------------------------*/
/* Module level contants */
#define PR_PREFIX                "<pr_Ownership "
#define PR_SUFFIX_S              ">"
#define PR_SUFFIX_C              '>'
#define PR_ITERABLE_CONSTS_COUNT 16
#define PR_NONE                  PR_ITERABLE_CONSTS_COUNT
#define PR_ALL                   17
#define PR_UNKNOWN               18
static const char *const pr_OWNERSHIPS[] =
{
    [PR_NONE]    = "pr_OWNS_NONE",
    [PR_ALL]     = "pr_OWNS_ALL",
    [0]          = "pr_OWNS_SELF",
    [1]          = "pr_OWNS_ATTR_1",
    [2]          = "pr_OWNS_ATTR_2",
    [3]          = "pr_OWNS_ATTR_3",
    [4]          = "pr_OWNS_ATTR_4",
    [5]          = "pr_OWNS_ATTR_5",
    [6]          = "pr_OWNS_ATTR_6",
    [7]          = "pr_OWNS_ATTR_7",
    [8]          = "pr_OWNS_ATTR_8",
    [9]          = "pr_OWNS_ATTR_9",
    [10]         = "pr_OWNS_ATTR_10",
    [11]         = "pr_OWNS_ATTR_11",
    [12]         = "pr_OWNS_ATTR_12",
    [13]         = "pr_OWNS_ATTR_13",
    [14]         = "pr_OWNS_ATTR_14",
    [15]         = "pr_OWNS_ATTR_15",
    [PR_UNKNOWN] = "(UNKNOWN)",
};



/*----------------------------------------------------------------------------*/
/* Public constants */
const pr_Ownership pr_OWNS_NONE    =  0u,
                   pr_OWNS_ALL     = ~0u,
                   pr_OWNS_SELF    = 1u << 0,
                   pr_OWNS_ATTR_1  = 1u << 1,
                   pr_OWNS_ATTR_2  = 1u << 2,
                   pr_OWNS_ATTR_3  = 1u << 3,
                   pr_OWNS_ATTR_4  = 1u << 4,
                   pr_OWNS_ATTR_5  = 1u << 5,
                   pr_OWNS_ATTR_6  = 1u << 6,
                   pr_OWNS_ATTR_7  = 1u << 7,
                   pr_OWNS_ATTR_8  = 1u << 8,
                   pr_OWNS_ATTR_9  = 1u << 9,
                   pr_OWNS_ATTR_10 = 1u << 10,
                   pr_OWNS_ATTR_11 = 1u << 11,
                   pr_OWNS_ATTR_12 = 1u << 12,
                   pr_OWNS_ATTR_13 = 1u << 13,
                   pr_OWNS_ATTR_14 = 1u << 14,
                   pr_OWNS_ATTR_15 = 1u << 15;



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
const char*
pr_Ownership_str(pr_Ownership self)
{
         if (self == pr_OWNS_NONE)    return pr_OWNERSHIPS[PR_NONE];
    else if (self == pr_OWNS_ALL)     return pr_OWNERSHIPS[PR_ALL];
    else if (self &  pr_OWNS_SELF)    return pr_OWNERSHIPS[0];
    else if (self &  pr_OWNS_ATTR_1)  return pr_OWNERSHIPS[1];
    else if (self &  pr_OWNS_ATTR_2)  return pr_OWNERSHIPS[2];
    else if (self &  pr_OWNS_ATTR_3)  return pr_OWNERSHIPS[3];
    else if (self &  pr_OWNS_ATTR_4)  return pr_OWNERSHIPS[4];
    else if (self &  pr_OWNS_ATTR_5)  return pr_OWNERSHIPS[5];
    else if (self &  pr_OWNS_ATTR_6)  return pr_OWNERSHIPS[6];
    else if (self &  pr_OWNS_ATTR_7)  return pr_OWNERSHIPS[7];
    else if (self &  pr_OWNS_ATTR_8)  return pr_OWNERSHIPS[8];
    else if (self &  pr_OWNS_ATTR_9)  return pr_OWNERSHIPS[9];
    else if (self &  pr_OWNS_ATTR_10) return pr_OWNERSHIPS[10];
    else if (self &  pr_OWNS_ATTR_11) return pr_OWNERSHIPS[11];
    else if (self &  pr_OWNS_ATTR_12) return pr_OWNERSHIPS[12];
    else if (self &  pr_OWNS_ATTR_13) return pr_OWNERSHIPS[13];
    else if (self &  pr_OWNS_ATTR_14) return pr_OWNERSHIPS[14];
    else if (self &  pr_OWNS_ATTR_15) return pr_OWNERSHIPS[15];
    else                              return pr_OWNERSHIPS[PR_UNKNOWN];
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Ownership_fput(pr_Ownership  self,
                  FILE         *stream)
{
    /* Local variables */
    int  i;
    bool nth;

    #ifndef PR_FAST
        /* If stream is NULL */
        if (!stream)
            return 0;
    #endif

    /* Print representation */
    fputs(PR_PREFIX, stream);
    /* If pr_OWNS_NONE */
    if (!self)
        fputs(pr_OWNERSHIPS[PR_NONE], stream);
    /* If pr_OWNS_ALL */
    else if (self == pr_OWNS_ALL)
        fputs(pr_OWNERSHIPS[PR_ALL], stream);
    /* If other or invalid pr_OWNS* constant */
    else
    {
        nth = false;
        for (i=0; i<PR_ITERABLE_CONSTS_COUNT; ++i)
            if (self & ((pr_Ownership)1 << i))
            {
                if (nth)
                    fputc('|', stream);
                fputs(pr_OWNERSHIPS[i], stream);
                nth = true;
            }
        /* If no valid constant found */
        if (!nth)
            fputs(pr_OWNERSHIPS[PR_UNKNOWN], stream);
    }
    fputc(PR_SUFFIX_C, stream);

    /* Return the number of bytes that has been written to stream */
    return pr_Ownership_sput_len(self);
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Ownership_put(pr_Ownership self)
{
    return pr_Ownership_fput(self, stdout);
}



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Ownership_sput(pr_Ownership  self,
                  size_t        length,
                  char         *buffer)
{
    /* Local variables */
    int    i;
    bool   nth;
    size_t start,
           required;

    /* If length is 0 or buffer is NULL */
    if (!length ||
        !buffer)
            return 0;

    /* Write prefix to buffer */
    start = --length;
    required = min(length, (sizeof PR_PREFIX) - 1);
    memcpy(buffer, PR_PREFIX, required);
    buffer += required;
    length -= required;

    /* If owns is pr_OWNS_NONE */
    if (!self)
    {
        required = min(length, strlen(pr_OWNERSHIPS[PR_NONE]));
        memcpy(buffer, pr_OWNERSHIPS[PR_NONE], required);
        buffer += required;
        length -= required;
    }
    /* If owns is pr_OWNS_ALL */
    else if (self == pr_OWNS_ALL)
    {
        required = min(length, strlen(pr_OWNERSHIPS[PR_ALL]));
        memcpy(buffer, pr_OWNERSHIPS[PR_ALL], required);
        buffer += required;
        length -= required;
    }
    /* If other or invalid pr_OWNS* constant */
    else
    {
        nth = false;
        for (i=0; length && i<PR_ITERABLE_CONSTS_COUNT; ++i)
            if (self & ((pr_Ownership)1 << i))
            {
                if (nth)
                {
                    required = min(length, 1);
                    memcpy(buffer, "|", required);
                    buffer += required;
                    length -= required;
                }
                required = min(length, strlen(pr_OWNERSHIPS[i]));
                memcpy(buffer, pr_OWNERSHIPS[i], required);
                buffer += required;
                length -= required;
                nth = true;
            }
        /* If no valid constant found */
        if (!nth)
        {
            required = min(length, strlen(pr_OWNERSHIPS[PR_UNKNOWN]));
            memcpy(buffer, pr_OWNERSHIPS[PR_UNKNOWN], required);
            buffer += required;
            length -= required;
        }
    }

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
pr_Ownership_sput_len(pr_Ownership self)
{
    /* Local varaibles */
    int    i;
    bool   nth;
    size_t length = sizeof PR_PREFIX PR_SUFFIX_S;

    /* If owns is pr_OWNS_NONE */
    if (!self)
        return length + strlen(pr_OWNERSHIPS[PR_NONE]);
    /* If owns is pr_OWNS_ALL */
    else if (self == pr_OWNS_ALL)
        return length + strlen(pr_OWNERSHIPS[PR_ALL]);
    /* If other or invalid pr_OWNS* constant */
    else
    {
        nth = false;
        for (i=0; i<PR_ITERABLE_CONSTS_COUNT; ++i)
            if (self & ((pr_Ownership)1 << i))
            {
                if (nth)
                    ++length;
                length += strlen(pr_OWNERSHIPS[i]);
                nth = true;
            }
        /* If no valid constant found */
        if (!nth)
            length += strlen(pr_OWNERSHIPS[PR_UNKNOWN]);
    }
    return length;
}

#undef PR_UNKNOWN
#undef PR_ALL
#undef PR_NONE
#undef PR_ITERABLE_CONSTS_COUNT
#undef PR_PREFIX
#undef PR_SUFFIX_S
#undef PR_SUFFIX_C
