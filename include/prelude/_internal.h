/* INFO **
** INFO */

/* Header guard */
#ifndef PR__INTERNAL_H_5167704331619651
#define PR__INTERNAL_H_5167704331619651 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */

/*----------------------------------------------------------------------------*/
static inline size_t
min(size_t a,
    size_t b)
{
    return a < b ? a : b;
}

#endif /* PR__INTERNAL_H_5167704331619651 */
