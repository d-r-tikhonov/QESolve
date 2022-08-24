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

/// Набор возможных состояний корней уравнения
enum caseSolutions {
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

short SolveQE(double a, double b, double c, double *firstR, double *secondR)
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

bool zeroNH(double n)
{
    const double epsilon = 1.e-7;
    return n <= epsilon && n >= -epsilon;
}
