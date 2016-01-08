/* INFO **
** INFO */

/* Header guard */
#ifndef PR_POINTER_H_4342666479125375
#define PR_POINTER_H_4342666479125375 1

/*  The pr_Pointer is a convertible pointer type capable of holding all kinds of
    pointers in C, while it is also strictly conforming and therefore portable.
    This header contains the necessary types, their methods and macros to
    implement such feature.

    The rationale behind this type is that the plain pointer to void may or may
    not have the same size as a function pointer. (A pointer to void is only
    capable of storing any type of object pointer, not function pointer. Also
    the representation of a pointer to function is implementation defined.)
    Therefore it is not conforming and portable to store pointer to function in
    pointer to void. However the standard clearly states, that any pointer to a
    function is capable of holding pointer to any kind of other function. (Even
    then, the stored function should not be called until it is properly casted
    first, otherwise it is undefined behaviour.) */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  type  : FILE
    value : stdout */
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
    /*  Set pr_Pointer instance to store an object pointer.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
                    DATA => can be any type of object pointer and NULL
        Return    : DATA casted to pointer to void. If PR_FAST is not defined,
                    on error NULL will be returned
        Prototype :
            void*
            pr_Pointer_ini_data(pr_Pointer *self,
                                <object>    pointer); */
    #ifdef PR_FAST
        #define pr_Pointer_set_data(SELF, DATA)                                \
            ((SELF)->type = pr_Pointer_DATA,                                   \
             (SELF)->data = (void *)(DATA))
    #else
        #define pr_Pointer_set_data(SELF, DATA)                                \
            ((SELF) ? ((SELF)->type = pr_Pointer_DATA,                         \
                       (SELF)->data = (void *)(DATA))                          \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Set pr_Pointer instance to store a function pointer.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
                    FUNC => can be any type of function pointer and NULL
        Return    : FUNC casted to pointer to function takes nothing and returns
                    void. If PR_FAST is not defined, on error NULL will be
                    returned
        Prototype :
            void (*)(void)
            pr_Pointer_ini_data(pr_Pointer *self,
                                <function>  pointer); */
    #ifdef PR_FAST
        #define pr_Pointer_set_func(SELF, FUNC)                                \
            ((SELF)->type = pr_Pointer_FUNC,                                   \
             (SELF)->func = (void(*)(void))(FUNC))
    #else
       #define pr_Pointer_set_func(SELF, FUNC)                                 \
            ((SELF) ? ((SELF)->type = pr_Pointer_FUNC,                         \
                       (SELF)->func = (void(*)(void))(FUNC))                   \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Get object pointer stored in pr_Pointer instance.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
        Return    : pointer to object, casted to pointer to void. If PR_FAST is
                    not defined, on error NULL will be returned
        Prototype :
            void*
            pr_Pointer_get_data(const pr_Pointer *self); */
    #ifdef PR_FAST
        #define pr_Pointer_get_data(SELF) ((SELF)->data)
    #else
        #define pr_Pointer_get_data(SELF)                                      \
            ((SELF) ? ((SELF)->type == pr_Pointer_DATA ? (SELF)->data          \
                                                       : NULL)                 \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Get function pointer stored in pr_Pointer instance.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
        Return    : pointer to function takes nothing and returns void. If
                    PR_FAST is not defined, on error NULL will be returned
        Prototype :
            void (*)(void)
            pr_Pointer_get_func(const pr_Pointer *self); */
    #ifdef PR_FAST
        #define pr_Pointer_get_func(SELF) ((SELF)->func)
    #else
        #define pr_Pointer_get_func(SELF)                                      \
            ((SELF) ? ((SELF)->type == pr_Pointer_FUNC ? (SELF)->func          \
                                                       : NULL)                 \
                    : NULL)
    #endif /* PR_FAST */
/* C89 and C99 */
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

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Set pr_Pointer instance to store an object pointer.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
                    DATA => can be any type of object pointer and NULL
        Return    : DATA casted to pointer to void. If PR_FAST is not defined,
                    on error NULL will be returned
        Prototype :
            void*
            pr_Pointer_ini_data(pr_Pointer *self,
                                <object>    pointer); */
    #ifdef PR_FAST
        #define pr_Pointer_set_data(SELF, DATA)                                \
            ((SELF)->type       = pr_Pointer_DATA,                             \
             (SELF)->value.data = (void *)(DATA))
    #else
        #define pr_Pointer_set_data(SELF, DATA)                                \
            ((SELF) ? ((SELF)->type       = pr_Pointer_DATA,                   \
                       (SELF)->value.data = (void *)(DATA))                    \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Set pr_Pointer instance to store a function pointer.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
                    FUNC => can be any type of function pointer and NULL
        Return    : FUNC casted to pointer to function takes nothing and returns
                    void. If PR_FAST is not defined, on error NULL will be
                    returned
        Prototype :
            void (*)(void)
            pr_Pointer_ini_data(pr_Pointer *self,
                                <function> pointer); */
    #ifdef PR_FAST
        #define pr_Pointer_set_func(SELF, FUNC)                                \
            ((SELF)->type = pr_Pointer_FUNC,                                   \
             (SELF)->func = (void(*)(void))(FUNC))
    #else
       #define pr_Pointer_set_func(SELF, FUNC)                                 \
            ((SELF) ? ((SELF)->type       = pr_Pointer_FUNC,                   \
                       (SELF)->value.func = (void(*)(void))(FUNC))             \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Get object pointer stored in pr_Pointer instance.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
        Return    : pointer to object, casted to pointer to void. If PR_FAST is
                    not defined, on error NULL will be returned
        Prototype :
            void*
            pr_Pointer_get_data(const pr_Pointer *self); */
    #ifdef PR_FAST
        #define pr_Pointer_get_data(SELF) ((SELF)->value.data)
    #else
        #define pr_Pointer_get_data(SELF)                                      \
            ((SELF) ? ((SELF)->type == pr_Pointer_DATA ? (SELF)->value.data    \
                                                       : NULL)                 \
                    : NULL)
    #endif /* PR_FAST */

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Get function pointer stored in pr_Pointer instance.
        Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
        Return    : pointer to function takes nothing and returns void. If
                    PR_FAST is not defined, on error NULL will be returned
        Prototype :
            void (*)(void)
            pr_Pointer_get_func(const pr_Pointer *self); */
    #ifdef PR_FAST
        #define pr_Pointer_get_func(SELF) ((SELF)->value.func)
    #else
        #define pr_Pointer_get_func(SELF)                                      \
            ((SELF) ? ((SELF)->type == pr_Pointer_FUNC ? (SELF)->value.func    \
                                                       : NULL)                 \
                    : NULL)
    #endif /* PR_FAST */

#endif /* __STDC_VERSION__ */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Initialize pr_Pointer instance, if PR_FAST is not defined.
    Arguments : SELF => has to be non NULL
    Return    : void
    Prototype :
        void
        pr_Pointer_ini(pr_Pointer *self); */
#ifdef PR_FAST
    #define pr_Pointer_ini(SELF) ((void)0)
#else
    #define pr_Pointer_ini(SELF) \
        ((void)((SELF) ? ((SELF)->type = pr_Pointer_NONE) : 0))
#endif /* PR_FAST */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Finalize pr_Pointer instance, if PR_FAST is not defined.
    Arguments : SELF => has to be non NULL
    Return    : void
    Prototype :
        void
        pr_Pointer_fin(pr_Pointer *self); */
#define pr_Pointer_fin(SELF) pr_Pointer_ini(SELF)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Get pointer's type stored in pr_Pointer instance.
    Arguments : SELF => has to be non NULL (unhandled: PR_FAST)
    Return    : pr_Pointer_NONE => nothing is stored or self is NULL
                pr_Pointer_DATA => object pointer is stored
                pr_Pointer_FUNC => function pointer is stored
    Prototype :
        <pr__PointerType> // type only has name if standard < C11
        pr_Pointer_get_type(const pr_Pointer *self); */
#ifdef PR_FAST
    #define pr_Pointer_get_type(SELF) ((SELF)->type)
#else
    #define pr_Pointer_get_type(SELF) \
        ((SELF) ? ((SELF)->type) : pr_Pointer_NONE)
#endif /* PR_FAST */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Get the string representation of a pr_Pointer instance
    Arguments : self => has to be non NULL (unhandled: PR_FAST)
    Return    : a globally available constant pointer */
const char*
pr_Pointer_str(const pr_Pointer *self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Write qualified string representation of pr_Pointer instance to 'stdout'.
    Arguments : self   => has to be non NULL (unhandled: PR_FAST)
    Return    : the number of bytes that has been written to 'stdout'
    Prototype :
        size_t
        pr_Pointer_put(const pr_Pointer *self); */
#define pr_Pointer_put(SELF) pr_Pointer_fput((SELF), stdout)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Write qualified string representation of pr_Pointer instance to 'stream'.
    Arguments : self   => has to be non NULL (unhandled: PR_FAST)
                stream => has to be non NULL (unhandled: PR_FAST)
    Return    : the number of bytes that has been written to 'stream' */
size_t
pr_Pointer_fput(const pr_Pointer *self,
                FILE             *stream);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Write qualified string representation of pr_Pointer instance to 'buffer'. It
    is guaranteed that if there were no errors, the string in the buffer will be
    null terminated.
    Arguments : length => has to be greater than 0 (unhandled: PR_FAST)
                stream => has to be non NULL (unhandled: PR_FAST)
    Return    : the number of bytes that has been written to 'stream' */
size_t
pr_Pointer_sput(const pr_Pointer *self,
                size_t            length,
                char             *buffer);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Return : necessary buffer size able to store qualified string
            representation of pointer */
size_t
pr_Pointer_sput_len(const pr_Pointer *self);

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* TODO: find a away to tell the max value during compilation */
/* This value represents the maximum buffer length required to store the
   qualified representation of pointer */
// #define PR_POINTER_MAX_SPUT_LEN ((size_t)259)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Compare two pr_Pointer instances to each other.
    Arguments : self  => has to be non NULL
                other => has to be non NULL
    Return    : pr_EQUAL              => the two pointers are the same
                pr_NOT_EQUAL          => the two pointers are not the same
                pr_UNCOMPARABLE_LEFT  => self is NULL
                pr_UNCOMPARABLE_RIGHT => other is NULL
                pr_UNCOMPARABLE       => different or invalid pointer types */
pr_Order
pr_Pointer_cmp(const pr_Pointer *self,
               const pr_Pointer *other);

/* TODO: add pr_Pointer_bool() and pr_Pointer_hash() methods */

#endif /* PR_POINTER_H_4342666479125375 */
