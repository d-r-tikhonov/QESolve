#include <stdio.h>
#include <math.h>
#include "quad_equ_solver.h"
#include "unit_tests.h"
#include "additional_functions.h"


/// Set of possible states of the roots of the equation
enum caseSolutions{
    NO_ROOTS,   ///< Indicates that the equation has no roots
    ONE_ROOT,   ///< Indicates that the equation has one root
    TWO_ROOTS,  ///< Indicates that the equation has two roots
    INF_ROOTS   ///< Indicates that the equation has an infinite set of roots
};


/// \brief                  To tests one specific case
/// \param[in]  a           Senior coefficient (coefficient at x^2)
/// \param[in]  b           Average coefficient (coefficient at x)
/// \param[in]  c           Free member
/// \param[in] nRoots_real  Expected number of roots
/// \param[in]  x1_real     The expected first root of the equation
/// \param[in]  x2_real     The expected second root of the equation
void testQE(float a, float b, float c, short nRoots_real, float x1_real, float x2_real)
{
    float x1 = 0.0;
    float x2 = 0.0;
	short nRoots = 0;

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("a = %.2f, b = %.2f, c = %.2f. ", a, b, c);

	nRoots = SolveQE(a, b, c, &x1, &x2);

	error(nRoots, x1, x2, nRoots_real, x1_real, x2_real);
}


/// \brief                  Displays a message about successful or unsuccessful verification
/// \param[in]  nRoots      The number of roots issued by the program
/// \param[in]  x1          The first root issued by the program
/// \param[in]  x2          The second root issued by the program
/// \param[in] nRoots_real  Expected number of roots
/// \param[in]  x1_real     The expected first root of the equation
/// \param[in]  x2_real     The expected second root of the equation 
void error(short nRoots, float x1, float x2, short nRoots_real, float x1_real, float x2_real)
{
	if(!(nRoots == nRoots_real && isEqFloat(x1, x1_real) && isEqFloat(x2, x2_real)))
	{
		printf("\nFAILED:   nRoots = %d, x1 = %f, x2 = %f\n"
                 "EXPECTED: nRoots = %d, x1 = %f, x2 = %f\n", nRoots, x1, x2, nRoots_real, x1_real, x2_real);
	}
	else
	{
        printf("\nSTATUS: Successful! The check was successful.\n");
    }
}

/// \brief A function containing a set of values for tests
void unit_tests(void)
{
    float a[] = 		  { 1, 0, 0, 49, 0, NAN, 1337};
    float b[] = 		  { 0, 0, 0,  7, 2,   0,  NAN};
    float c[] = 		  {-2, 0, 2, -2, 5,  50,  228};
    short nRoots_real[] = {TWO_ROOTS,INF_ROOTS, NO_ROOTS, TWO_ROOTS, ONE_ROOT, 0, 0};
    float x1_real[] = 		  { sqrt(2), 0, 0,  0.142857, -2.5, 0, 0};
    float x2_real[] = 		  {-sqrt(2), 0, 0, -0.285714, -2.5, 0, 0};

    for (unsigned unitCounter = 0; unitCounter < sizeof(a)/sizeof(a[0]); unitCounter++)
    {
        testQE(a[unitCounter], b[unitCounter], c[unitCounter], nRoots_real[unitCounter],
            x1_real[unitCounter], x2_real[unitCounter]);
    }
}