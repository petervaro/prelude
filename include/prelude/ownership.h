/* INFO **
** INFO */

/* Header guard */
#ifndef PR_OWNERSHIP_H_4129475682998757
#define PR_OWNERSHIP_H_4129475682998757 1

/*  pr_Ownership can be used, to indicate and store ownership status between the
    members and the proxy object. An object is called 'proxy' if it contains at
    least a single pointer as a member. */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <stdio.h>
/*  type  : FILE */
#include <stddef.h>
/*  type  : size_t */

/*----------------------------------------------------------------------------*/
typedef unsigned int pr_Ownership;

/*----------------------------------------------------------------------------*/
extern const pr_Ownership pr_OWNS_NONE,
                          pr_OWNS_ALL,
                          pr_OWNS_SELF,
                          pr_OWNS_ATTR_1,
                          pr_OWNS_ATTR_2,
                          pr_OWNS_ATTR_3,
                          pr_OWNS_ATTR_4,
                          pr_OWNS_ATTR_5,
                          pr_OWNS_ATTR_6,
                          pr_OWNS_ATTR_7,
                          pr_OWNS_ATTR_8,
                          pr_OWNS_ATTR_9,
                          pr_OWNS_ATTR_10,
                          pr_OWNS_ATTR_11,
                          pr_OWNS_ATTR_12,
                          pr_OWNS_ATTR_13,
                          pr_OWNS_ATTR_14,
                          pr_OWNS_ATTR_15;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : String representation of ownership. Because pr_Ownership can be a
            bit-masked value, this method will return the lowest value folded
            into 'owns'. If proper value is needed, one should unfold the
            possible values separately and pass them to this method if they are
            present */
const char*
pr_Ownership_str(pr_Ownership self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified string representation of ownership to stream */
size_t
pr_Ownership_fput(pr_Ownership  self,
                  FILE         *stream);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified string representation of ownership to 'stdout' */
size_t
pr_Ownership_put(pr_Ownership self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified string representation of ownership to buffer */
size_t
pr_Ownership_sput(pr_Ownership  self,
                  size_t        length,
                  char         *buffer);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : necessary buffer size able to store qualified string
            representation of ownership */
size_t
pr_Ownership_sput_len(pr_Ownership self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This value represents the maximum buffer length required to store the
   qualified representation of ownership */
#define PR_OWNERSHIP_MAX_SPUT_LEN ((size_t)259)

#endif /* PR_OWNERSHIP_H_4129475682998757 */
