#include <stdio.h>
#include <TXlib.h>

short SolveQE(double a, double b, double c, double *x1, double *x2);

int main(void){

	double seniorCoeff = 0.0;
	double averageCoeff = 0.0;
	double freeTerm = 0.0;
	double firstR = 0.0;
	double secondR = 0.0;
	short nRoots = 0;

	printf ("Введите старший коэффицент: ");
	scanf ("%lf", &seniorCoeff);
	printf ("Введите средний коэффицент: ");
	scanf ("%lf", &averageCoeff);
	printf ("Введите свободный член: ");
	scanf ("%lf", &freeTerm);

	nRoots = SolveQE(seniorCoeff, averageCoeff, freeTerm, &firstR, &secondR);

	switch(nRoots){
		case 0:
            printf("Ваше уравнение не имеет корней.");
           	break;
		case 1:
			printf("Ваше уравнение имеет 1 корень: %.2lf.", firstR);
			break;
		case 2:
			printf("Ваше уравнение - квадратное и имеет 2 корня: x1 = %.2lf и x2 = %.2lf.", firstR, secondR);
			break;
		default:
			printf("Ваше уравнение имеет бесконечно много корней.");
			break;
	}

	return 0;
}

short SolveQE(double a, double b, double c, double *firstR, double *secondR){

	double discriminant = 0.0;

	if (a == 0)
	{
		if (b != 0)
		{
			*firstR=*secondR=(-c)/(b);
			return 1;
        }
		else if (c == 0)
			return -1;
		else
			return 0;
	}

	discriminant = b*b - 4*a*c;

	if (a != 0){

		if (discriminant < 0)
			return 0;

		if (discriminant == 0)
		{
			*firstR = *secondR = (-b)/(2*a);
			return 1;
        }

		if (discriminant > 0)
		{
			*firstR = ((-b + sqrt(discriminant))/(2*a));
			*secondR = ((-b - sqrt(discriminant))/(2*a));
			return 2;
        }
	}
}
