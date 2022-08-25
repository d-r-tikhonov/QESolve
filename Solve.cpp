/*! \mainpage Программа для решения квадратных уравнений
 *
 * Этот проект поможет Вам решить линейное или квадратное уравнение.
 * - \ref Вы можете вводить любые символы и буквы, программа предусматривает это.
 * - \ref Съешь ещё этих мягких французских булочек!
 * - \subpage userGuide "Как пользоваться программой?"
 * - \subpage authors 	"Авторы программы"
 */

/*! \page userGuide Как пользоваться программой?
 *
 * Это страница о том, как пользоваться этой программой.
 * - \ref Берёшь и пользуешься (:
 * - \ref Meow
 * - \ref Purr
 */

/*! \page authors Авторы программы
 *
 * \authors Тихонов Д.Р.
 * \version 1.4
 * \date 		Август, 2022
 * \bug 		Пока не найдены.
 * \warning 	Таких нет.
 * \copyright	Copyright © 2022 Дмитрий Тихонов. Все права защищены.
 * \todo 		Сделать юнит-тесты.
 */
#include <stdio.h>
#include <TXlib.h>
#include <math.h>
#include <assert.h>

///    Находит количество корней квадратного (или линейного) уравнения
///    \param a,b,c Коэффициента в уравнении (начиная со старшего)
///    \return Количество корней квадратного уравнения, и сами корни
short SolveQE(double a, double b, double c, double *x1, double *x2);
///    Выводит решения уравнения
///    \param nRoots 	Количество корней уравнения
///    \param x1 		Значение первого корня уравнения
///	   \param x2 		Значение второго корня уравнения
///    \return 			Количество корней квадратного уравнения, и сами корни
void conSol(int nRoots, double x1, double x2);
///    Проверяет находится ли число в окрестности нуля
///    \param 	n 	Число, которое подлежит проверке
///    \return		True, в случае, если число лежит в окрестности нуля, false - в ином случае
bool zeroNH(double n);
bool equivalentNH(double n, double equivalent);
void testQE(double a, double b, double c,short nRoots_real, double x1_real, double x2_real);
void error(short nRoots, double x1, double x2, short nRoots_real, double x1_real, double x2_real);
/// Набор возможных состояний корней уравнения

enum caseSolutions{
    NO_ROOTS,	///< Указывает, что у уравнения нет корней
    ONE_ROOT,	///< Указывает, что у уравнения один корень
    TWO_ROOTS,	///< Указывает, что у уравнения два корня
    INF_ROOTS 	///< Указывает, что у уравнения бесконечное множество корней
};

///    \param[in]  sCoeff      Старший коэффициент (коэффициент при х^2)
///    \param[in]  aCoeff      Средний коэффициент (коэффициент при х)
///    \param[in]  fTerm       Свободный член
///    \param[out] firstR      Первый корень уравнения
///    \param[out] secondR     Второй корень уравнения

/*!
	\code
	int main(void)
	{
		double sCoeff = 0.0;
		double aCoeff = 0.0;
		double fTerm = 0.0;
		double firstR = 0.0;
		double secondR = 0.0;
		short nRoots = 0;
		bool quit = false;
		char testForQuit = 0;

		do
		{
      	  printf ("Введите коэффициенты уравнения (через пробел), для выхода - 'q': ");
    		if (scanf ("%lf%lf%lf", &sCoeff, &aCoeff, &fTerm) == 3)
    		{
        		nRoots = SolveQE (sCoeff, aCoeff, fTerm, &firstR, &secondR);
        		conSol (nRoots, firstR, secondR);
    		}
   			else
   			{
          	  scanf("%c",&testForQuit);
        		if (testForQuit == 'q') quit = true;
        		else printf("Вы допустили ошибку при вводе!\n");
    		}
		}
		while (!quit);

    	return 0;
	}
	\endcode
*/
int main(void)
{

	double sCoeff = 0.0;
	double aCoeff = 0.0;
	double fTerm = 0.0;
	double firstR = 0.0;
	double secondR = 0.0;
	short nRoots = 0;
	bool quit = false;
	char ansUser = 0;

	printf("Выберите режим работы программы ('s' - для решения уравнения, 't' - для юнит-тестов): ");
	scanf("%c", &ansUser);

	if(ansUser == 's')
	{
		do
		{
	        printf ("Введите коэффициенты уравнения (через пробел), для выхода - 'q': ");
	    	if (scanf ("%lf%lf%lf", &sCoeff, &aCoeff, &fTerm) == 3)
	    	{
	        	nRoots = SolveQE (sCoeff, aCoeff, fTerm, &firstR, &secondR);
	        	conSol (nRoots, firstR, secondR);
	    	}
	   		else
	   		{
	            scanf("%c",&ansUser);
	        	if (ansUser == 'q') quit = true;
	        	else printf("Вы допустили ошибку при вводе!\n");
	    	}
		}
		while (!quit);
	}

	if(ansUser == 't')
	{
		double a[] = {1,0,0,49,0};
		double b[] = {0,0,0,7,2};
		double c[] = {-2,0,2,-2,5};
		double nRoots_real[]= {2, INF_ROOTS, NO_ROOTS, TWO_ROOTS,ONE_ROOT};
		double x1[] = {sqrt(2),0,0,0.14,-2.5};
		double x2[] = {-sqrt(2),0,0,-0.28,-2.5};
		for (int i = 0; i <= sizeof(a)/sizeof(a[0]), i++)
		{
			testQE(a[i],b[i],c[i],nRoots_real[i],x1[i],x2[i]);
		}
	}

    return 0;
}

short SolveQE(double a, double b, double c, double *firstR, double *secondR)
{
	double discriminant = 0.0;

	if (zeroNH (a))
	{
		if (!zeroNH(b))
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

		if (discriminant < 0)
			return NO_ROOTS;

		if (zeroNH(discriminant))
		{
			*firstR = *secondR = -b/(2*a);
			return ONE_ROOT;
        }

		if (discriminant > 0)
		{
			double sqrt_d = sqrt(discriminant);
			*firstR = (-b + sqrt_d)/(2*a);
			*secondR = (-b - sqrt_d)/(2*a);
			return TWO_ROOTS;
        }

    return 0;
}

void conSol(int nRoots, double x1, double x2)
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

bool equivalentNH(double n, double equivalent)
{
    const double epsilon = 1.e-1;
    return n <= equivalent + epsilon && n >= equivalent-epsilon;
}

bool zeroNH(double n)
{
    const double epsilon = 1.e-1;
    return n <= epsilon && n >= -epsilon;
}

void testQE(double a, double b, double c,short nRoots_real, double x1_real, double x2_real)
{
    double x1 = 0.0;
    double x2 = 0.0;
	short nRoots = 0;
	printf("a = %.2lf, b = %.2lf, c = %.2lf. ",a,b,c);
	nRoots = SolveQE(a,b,c,&x1,&x2);
	error(nRoots, x1, x2, nRoots_real, x1_real, x2_real);
}

void error(short nRoots, double x1, double x2, short nRoots_real, double x1_real, double x2_real)
{

	if(!(nRoots == nRoots_real && equivalentNH(x1, x1_real) && equivalentNH(x2, x2_real)))
	{
		printf("FAILED: nRoots = %d, x1 = %lf, x2 = %lf\n"
               "EXPECTED: nRoots = %d, x1 = %lf, x2 = %lf\n", nRoots, x1, x2, nRoots_real, x1_real, x2_real);
	}
	else
	{
        printf("STATUS: Проверка прошла успешно\n");
    }
}
