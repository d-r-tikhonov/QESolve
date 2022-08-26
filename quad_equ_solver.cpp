#include <stdio.h>
#include <math.h>
#include "quad_equ_solver.h"
#include "additional_functions.h"


/// Set of possible states of the roots of the equation
enum caseSolutions{
    NO_ROOTS,	///< Indicates that the equation has no roots
    ONE_ROOT,	///< Indicates that the equation has one root
    TWO_ROOTS,	///< Indicates that the equation has two roots
    INF_ROOTS 	///< Indicates that the equation has an infinite set of roots
};


/// \brief				Finds the number of roots of a square (or linear) equation
/// \param[in] 	a 		Senior coefficient (coefficient at x^2)
/// \param[in] 	b 		Average coefficient (coefficient at x)
/// \param[in] 	c 		Free member
/// \param[in] 	f 		Free member
/// \return 		The number of roots of the quadratic equation, and the roots themselves
short SolveQE(float a, float b, float c, float *firstR, float *secondR)
{
	float discriminant = 0.0;

	if (isEqFloat(a,0))
	{
		if (!isEqFloat(b,0))
		{
			*firstR = *secondR = -c/(b);
			return ONE_ROOT;
        }
		else if (isEqFloat(c,0))
			return INF_ROOTS;
		else
			return NO_ROOTS;
	}

	discriminant = b*b - 4*a*c;

		if (discriminant < 0)
			return NO_ROOTS;

		float doubled_a = 2*a;

		if (isEqFloat(discriminant,0))
		{
			*firstR = *secondR = -b/doubled_a;
			return ONE_ROOT;
        }

		if (discriminant > 0)
		{
			float sqrt_d = sqrt(discriminant);
			*firstR = (-b + sqrt_d)/doubled_a;
			*secondR = (-b - sqrt_d)/doubled_a;
			return TWO_ROOTS;
        }

    return 0;
}


/// \brief			  	Outputs solutions of the equation
/// \param[in] 	nRoots 	The number of roots of the equation
/// \param[in] 	x1 		Value of the first root of the equation
/// \param[in] 	x2 		Value of the second root of the equation
/// \return 			The number of roots of the quadratic equation, and the roots themselves
void outputSolutions(int nRoots, float x1, float x2)
{
    switch (nRoots){
		case NO_ROOTS:
            printf ("Your equation has no roots.\n");
           	break;

		case ONE_ROOT:
			printf ("Your equation has 1 root: %.2f.\n", x1);
			break;

		case TWO_ROOTS:
			printf ("Your equation is square and has 2 roots: x1 = %.2f and x2 = %.2f.\n", x1, x2);
			break;

		case INF_ROOTS:
			printf ("Your equation has infinitely many roots.\n");
			break;

        default:
            printf("ERROR: there is no such value for the roots of the equation!");
	}
}