/* INFO **
** INFO */

/* TEST SWITCH */
// #define PR_FAST 1
/* TEST SWITCH */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : printf */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include prelude headers */
#include "prelude/pointer.h"
/*  type  : pr_Pointer
    const : pr_Pointer_NONE
            pr_Pointer_DATA
            pr_Pointer_FUNC */

/*----------------------------------------------------------------------------*/
double
function(double number);



/*----------------------------------------------------------------------------*/
int
main(void)
{
    /* TODO: write proper tests! (eg. test invalid values) */

    double n,
           number = 0.3333333333333333;
    double (*f)(double);
    pr_Pointer np,
               fp;

    pr_Pointer_ini(&np);
    pr_Pointer_ini(&fp);

    pr_Pointer_set_data(&np, &number);
    pr_Pointer_set_func(&fp, function);

    pr_Pointer_put(&np); puts("");
    pr_Pointer_put(&fp); puts("");

    n = *(double *)pr_Pointer_get_data(&np);
    f = (double(*)(double))pr_Pointer_get_func(&fp);
    printf("%f\n", f(n));

    pr_Pointer_fin(&np);
    pr_Pointer_fin(&fp);
    return EXIT_SUCCESS;
}



/*----------------------------------------------------------------------------*/
double
function(double number)
{
    return number/number/number;
}
