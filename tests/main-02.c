/* INFO **
** INFO */

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
    double n,
           number = 0.123456789;
    double (*f)(double);
    pr_Pointer np,
               fp;

    pr_Pointer_ini(np);
    pr_Pointer_ini(fp);

    pr_Pointer_set_data(np, &number);
    pr_Pointer_set_func(fp, function);

    n = *(double *)pr_Pointer_get_data(np);
    f = (double(*)(double))pr_Pointer_get_func(fp);
    printf("%f\n", f(n));

    pr_Pointer_fin(np);
    pr_Pointer_fin(fp);
    return EXIT_SUCCESS;
}



/*----------------------------------------------------------------------------*/
double
function(double number)
{
    return number/number/number;
}
