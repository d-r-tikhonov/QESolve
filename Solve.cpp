/*! \mainpage 			A program for solving quadratic equations
 *
 * - \ref 				This project will help you solve a linear or quadratic equation.
 * - \ref 				You can enter any characters and letters, the program provides for this.
 * 
 * - \subpage guide 	"How to use the program?"
 * - \subpage authors 	"Authors of the program"
 *
 */ 

/*! \page guide 				How to use the program?
 *
 * - \ref    					This is a page about how to use this program.
 * - \ref 						In development
 * 
 */

/*! \page authors 	Authors of the program
 * 
*   \authors 		Tikhonov D.R.
* 	\version 		1.4
* 	\date 			August, 2022
* 	\bug 			not found yet.
* 	\warning 		There are no such.
* 	\copyright 		Copyright © 2022 Dmitry Tikhonov. All rights reserved.
* 	\todo 			TODO LIST.
* 
*/


#include <stdio.h>
#include "quad_equ_solver.h"
#include "unit_tests.h"
#include "additional_functions.h"

/// \param[in] 	sCoeff 		Senior coefficient (coefficient at x^2)
/// \param[in] 	aCoeff 		Average coefficient (coefficient at x)
/// \param[in] 	fTerm 		Free member
/// \param[out] firstR 		The first root of the equation
/// \param[out] secondR 	The second root of the equation
int main(void)
{

	float sCoeff = 0.0;
	float aCoeff = 0.0;
	float fTerm = 0.0;
	float firstR = 0.0;
	float secondR = 0.0;
	short nRoots = 0;
	bool quit = false;
	char ansUser = 0;

	printf("Select the mode of operation of the program ('s' - for solving the equation, 't' - for unit tests): ");
	scanf("%c", &ansUser);

	if (ansUser == 's')
	{
		do
		{
	        printf ("Enter the coefficients of the equation (separated by a space), to exit - 'q': ");
	    	if (scanf ("%f%f%f", &sCoeff, &aCoeff, &fTerm) == 3)
	    	{
	        	nRoots = SolveQE (sCoeff, aCoeff, fTerm, &firstR, &secondR);
	        	outputSolutions (nRoots, firstR, secondR);
	    	}
	   		else
	   		{
	            scanf("%c",&ansUser);
	        	if (ansUser == 'q') quit = true;
	        	else
	        	{
                    printf("You made a mistake while typing!\n");
                    clearBuffer();
                }
	    	}
		}
		while (!quit);
	}

	if(ansUser == 't')
        unit_tests();

    getchar();
    getchar();

    return 0;
}