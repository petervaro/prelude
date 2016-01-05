/* INFO **
** INFO */

/* Header guard */
#ifndef PR_ORDER_H_1133440096313524
#define PR_ORDER_H_1133440096313524 1

/*  The pr_Order type can be used to compare complex, user-defined data types.
    The type is guaranteed to be an unsigned integer value, capable of storing a
    single ordering constant.

    The ordering constants are unique and can be used in both conditional
    statements and bit-mask unfolding.

    One can use them in a simple boolean comparison, as pr_EQUAL's boolean value
    is always false, while any other constant's value is true.

    One can use the constants for bit-mask unfolding, because all constants,
    except pr_EQUAL folds the value pr_NOT_EQUAL.

    Also, both pr_UNCOMPARABLE_LEFT and pr_UNCOMPARABLE_RIGHT constants fold the
    pr_UNCOMPARABLE constant. */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <stdio.h>
/*  type  : FILE */
#include <stddef.h>
/*  type  : size_t */

/*----------------------------------------------------------------------------*/
typedef unsigned char pr_Order;

/*----------------------------------------------------------------------------*/
extern const pr_Order pr_EQUAL,
                      pr_NOT_EQUAL,
                      pr_GREATER,
                      pr_LESSER,
                      pr_UNCOMPARABLE,
                      pr_UNCOMPARABLE_LEFT,
                      pr_UNCOMPARABLE_RIGHT;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : string representation of order */
const char*
pr_Order_str(pr_Order self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified representation of order to stream
   Return : the number of bytes that has been written to 'stream' */
size_t
pr_Order_fput(pr_Order  self,
              FILE     *stream);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified representation of order to stdout
   Return : the number of bytes that has been written to 'stdout' */
size_t
pr_Order_put(pr_Order self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Write qualified string representation of order to buffer
   Return : the number of bytes that has been written to 'buffer' */
size_t
pr_Order_sput(pr_Order  self,
              size_t    length,
              char     *buffer);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : necessary buffer size able to store qualified string
            representation of order */
size_t
pr_Order_sput_len(pr_Order self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This value represents the maximum buffer length required to store the
   qualified representation of order */
#define PR_ORDER_MAX_SPUT_LEN ((size_t)33)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : the opposite value of the passed order. For example, if pr_EQUAL
            passed, it will return pr_NOT_EQUAL. If it is any of the
            pr_UNCOMPARABLE* ones, it will return the same order as passed */
pr_Order
pr_Order_not(pr_Order self);

#endif /* PR_ORDER_H_1133440096313524 */
