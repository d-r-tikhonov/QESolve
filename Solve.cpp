#include <stdio.h>
#include <TXlib.h>
#include <math.h>
#include <assert.h>

short SolveQE (double a, double b, double c, double *x1, double *x2);
void conSol (int nRoots, double x1, double x2);
bool zeroNH (double n);

enum caseSolutions {
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

int main (void)
{
	double sCoeff = 0.0;
	double aCoeff = 0.0;
	double fTerm = 0.0;
	double firstR = 0.0;
	double secondR = 0.0;
	short nRoots = 0;

    printf("Введите коэффициенты уравнения (через пробел): ");

	while (scanf ("%lf%lf%lf", &sCoeff, &aCoeff, &fTerm) == 3)
	{
        nRoots = SolveQE (sCoeff, aCoeff, fTerm, &firstR, &secondR);
        conSol (nRoots, firstR, secondR);
        printf("Для следующей операции введите три коэффицинта (через пробел);\n");
        printf("Для выхода - любой нечисловой символ: ");
	}

    return 0;
}

short SolveQE (double a, double b, double c, double *firstR, double *secondR)
{
	double discriminant = 0.0;

	if (zeroNH (a))
	{
		if (!zeroNH (b))
		{
			*firstR = *secondR = -c/(b);
			return ONE_ROOT;
        }
		else if (zeroNH(c))
			return INF_ROOTS;
		else
			return NO_ROOTS;
	}

	discriminant = b*b - 4*a*c;
	double sqrt_d = sqrt(discriminant);

		if (discriminant < 0)
			return NO_ROOTS;

		if (zeroNH(discriminant))
		{
			*firstR = *secondR = -b/(2*a);
			return ONE_ROOT;
        }

		if (discriminant > 0)
		{
			*firstR = (-b + sqrt_d)/(2*a);
			*secondR = (-b - sqrt_d)/(2*a);
			return TWO_ROOTS;
        }

    return 0;
}

void conSol (int nRoots, double x1, double x2)
{
    switch (nRoots){
		case NO_ROOTS:
            printf ("Ваше уравнение не имеет корней.\n");
           	break;

		case ONE_ROOT:
			printf ("Ваше уравнение имеет 1 корень: %.2lf.\n", x1);
			break;

		case TWO_ROOTS:
			printf ("Ваше уравнение - квадратное и имеет 2 корня: x1 = %.2lf и x2 = %.2lf.\n", x1, x2);
			break;

		case INF_ROOTS:
			printf ("Ваше уравнение имеет бесконечно много корней.\n");
			break;

        default:
            printf("Unknown error!");
	}
}

bool zeroNH (double n)
{
    const double epsilon = 1.e-7;
    if (n <= epsilon && n >= -epsilon) return true;
    return false;
}
