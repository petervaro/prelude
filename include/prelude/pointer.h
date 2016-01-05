/* INFO **
** INFO */

/* Header guard */
#ifndef PR_POINTER_H_4342666479125375
#define PR_POINTER_H_4342666479125375 1

/*  The ap_AllPtr is a convertible pointer data type capable of holding all
    kinds of pointers in C while it is also strictly standard compilant and
    portable. This header contains the necessary data types to implement such
    feature and also a few macros, to interact with this type.

    Rationale:  The plain old `void *` may or may not have the same size as a
                function pointer, therefore it is not suitable for storing
                function pointers. The standard clearly states, that only a
                function pointer is capable of holding a pointer to a function.
                However any function pointer can hold all other types of
                function pointers (while this is perfectly legal, it worth
                mentioning that if one wants to call the stored function in a
                function pointer, one has to properly cast it first), therefore
                a function pointer can and should be used parallel with a
                `void *` to make a truly generic pointer type, and that's
                exactly what `ap_AllPtr` does. */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/order.h"
/*  type  : pr_Order */


/* C11 */
#if __STDC_VERSION__ >= 201112L

    /*------------------------------------------------------------------------*/
    typedef struct
    {
        enum
        {
            pr_Pointer_NONE,
            pr_Pointer_DATA,
            pr_Pointer_FUNC,
        } type;
        union
        {
            void  *data;
            void (*func)(void);
        };
    } pr_Pointer;


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void
       pr_Pointer_ini(pr_Pointer self); */
    #define pr_Pointer_ini(SELF) (SELF.type = pr_Pointer_NONE, (void)0)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void
       pr_Pointer_fin(pr_Pointer self); */
    #define pr_Pointer_fin(SELF) pr_Pointer_ini(SELF)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void*
       pr_Pointer_ini_data(pr_Pointer self,
                           <pointer>  data); */
    #define pr_Pointer_set_data(SELF, DATA)                                    \
        (SELF.type = pr_Pointer_DATA,                                          \
         SELF.data = (void *)(DATA))

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void (*)(void)
       pr_Pointer_ini_data(pr_Pointer self,
                           <function> func); */
    #define pr_Pointer_set_func(SELF, FUNC)                                    \
        (SELF.type = pr_Pointer_FUNC,                                          \
         SELF.func = (void (*)(void))(FUNC))

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void*
       pr_Pointer_get_data(pr_Pointer self); */
    #define pr_Pointer_get_data(SELF)                                          \
        (SELF.type == pr_Pointer_DATA ? SELF.data : NULL)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* void (*)(void)
       pr_Pointer_get_func(pr_Pointer self); */
    #define pr_Pointer_get_func(SELF)                                          \
        (SELF.type == pr_Pointer_FUNC ? SELF.func : NULL)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* <pr_Pointer_NONE or pr_Pointer_DATA or pr_Pointer_FUNC>
       pr_Pointer_get_type(pr_Pointer self); */
    #define pr_Pointer_get_type(SELF) (SELF.type)

/* C99 */
#elif __STDC_VERSION__ >= 199901L

/* C89 */
#else

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    typedef enum
    {
        pr_Pointer_NONE,
        pr_Pointer_DATA,
        pr_Pointer_FUNC
    } pr__PointerType;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    typedef union
    {
        void  *data;
        void (*func)(void);
    } pr__PointerValue;

    /*------------------------------------------------------------------------*/
    typedef struct
    {
        pr__PointerType  type;
        pr__PointerValue value;
    } pr_Pointer;

#endif /* __STDC_VERSION__ */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_str(const pr_Pointer *self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_fput(const pr_Pointer *self,
                FILE             *stream);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_put(const pr_Pointer *self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_sput(const pr_Pointer *self,
                size_t            length,
                char             *buffer);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
pr_Pointer_sput_len(const pr_Pointer *self);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : pr_EQUAL              => the two pointers are the same
            pr_NOT_EQUAL          => the two pointers are not the same
            pr_UNCOMPARABLE       => pointers have different types
            pr_UNCOMPARABLE_LEFT  => self is NULL
            pr_UNCOMPARABLE_RIGHT => other is NULL */
pr_Order
pr_Pointer_cmp(const pr_Pointer *self,
               const pr_Pointer *other);

#endif /* PR_POINTER_H_4342666479125375 */
