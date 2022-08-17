#include <stdio.h>
#include <TXlib.h>
#include "functions.h"

int main(void){

	double seniorCoeff = 0.0; /* переменная для старшего коэффициента уравнения */
	double averageCoeff = 0.0; /* переменная для среднего коэффициента уравнения */
	double freeTerm = 0.0; /* переменная для свободного члена уравнения */

	printf ("Введите старший коэффицент: ");
	scanf ("%lf", &seniorCoeff);
	printf ("Введите средний коэффицент: ");
	scanf ("%lf", &averageCoeff);
	printf ("Введите свободный член: ");
	scanf ("%lf", &freeTerm);

	if (seniorCoeff == 0)
	{
		if (averageCoeff != 0)
			lineRoot(averageCoeff, freeTerm);
		else if (freeTerm == 0)
			printf ("Ваше уравнение является линейным и имеет бесконечно много решений.");
		else
			printf("Ваше уравнение является линейным и не имеет решений.");
	}

	if (seniorCoeff != 0){

		if (discriminant(seniorCoeff, averageCoeff, freeTerm) < 0)
			negativeD();

		if (discriminant(seniorCoeff, averageCoeff, freeTerm) == 0)
			zeroD(seniorCoeff, averageCoeff);

		if (discriminant(seniorCoeff, averageCoeff, freeTerm) > 0)
			twoRoots(seniorCoeff, averageCoeff, freeTerm);
	}

	return 0;
}
