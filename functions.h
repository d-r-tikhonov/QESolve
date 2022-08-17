#include <stdio.h>

double discriminant(double a,double b, double c);
void twoRoots(double a,double b, double c);
void zeroD(double a,double b);
void negativeD(void);
void lineRoot(double b, double c);


double discriminant(double a,double b, double c){
	return b*b - 4*a*c;
}

void twoRoots(double a,double b, double c){
	printf ("Ваше уравнение - квадратное (D > 0), оно имеет 2 корня, равные x1 = %.2lf и x2 = %.2lf",
		((-b) + sqrt(discriminant(a,b,c))/(2*a)),(((-b) - sqrt(discriminant(a,b,c)))/(2*a)));
    return;
}

void zeroD(double a,double b){
	printf ("Ваше уравнение - квадратное (D = 0), оноимеет 1 решение, x = %.2lf\n", (-b)/(2*a));
	return;
}

void negativeD(void){
	printf ("Уравнение не имеет вещественных корней, так как дискриминант Вашего уравнения меньше нуля.\n");
	return;
}

void lineRoot(double b, double c){
	printf ("Ваше уравнение является линейным, у него 1 корень, x = %.2lf\n", (-c) / b);
	return;
}

