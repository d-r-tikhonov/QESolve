#include <stdio.h>
#include <TXlib.h>
#include <math.h>
#include <assert.h>

short SolveR (double a, double b, double c, double *x1, double *x2);
void SolveQE (int nRoots, double x1, double x2);
bool moduleN (double n);

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
	char ansUser = 0;

	while (true)
	{
        printf("Введите коэффициенты уравнения (через пробел): ");
        scanf ("%lf%lf%lf", &sCoeff, &aCoeff, &fTerm);

        nRoots = SolveR (sCoeff, aCoeff, fTerm, &firstR, &secondR);

        SolveQE (nRoots, firstR, secondR);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Желаете решить ещё одно уравнение?(y/n): ");
        getchar();
        ansUser = getchar();
        if (ansUser == 'n') break;
	}

    return 0;
}

short SolveR (double a, double b, double c, double *firstR, double *secondR)
{
	double discriminant = 0.0;

	assert (isfinite(a));
	assert (isfinite(b));
	assert (isfinite(c));

	if (moduleN (a))
	{
		if (!moduleN (b))
		{
			*firstR = *secondR = -c/(b);
			return ONE_ROOT;
        }
		else if (moduleN(c))
			return INF_ROOTS;
		else
			return NO_ROOTS;
	}

	discriminant = b*b - 4*a*c;
	double sqrt_d = sqrt(discriminant);

		if (discriminant < 0)
			return NO_ROOTS;

		if (moduleN(discriminant))
		{
			*firstR = *secondR = -b/(2*a);
			return ONE_ROOT;
        }

		if (discriminant > 0)
		{
			*firstR = ((-b + sqrt_d)/(2*a));
			*secondR = ((-b - sqrt_d)/(2*a));
			return TWO_ROOTS;
        }

    return 0;
}

void SolveQE (int nRoots, double x1, double x2)
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

bool moduleN (double n)
{
    const double epsilon = 1.e-7;
    if (n <= epsilon && n >= -epsilon) return true;
    return false;
}
