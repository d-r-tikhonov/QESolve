#include <stdio.h>
#include <TXlib.h>

int main(void){

	double seniorCoeff, averageCoeff, freeTerm, discriminant; /* переменные для хранения коэффицентов уравнения */

	seniorCoeff = 0.0;
	averageCoeff = 0.0;
	freeTerm = 0.0;
	discriminant = 0.0;

	printf("Введите старший коэффицент: \n");
	scanf("%lf", &seniorCoeff);
	printf("Введите средний коэффицент: \n");
	scanf("%lf", &averageCoeff);
	printf("Введите свободный член: \n");
	scanf("%lf", &freeTerm);

	discriminant = pow(averageCoeff,2) - 4*seniorCoeff*freeTerm;

	if(seniorCoeff == 0){
		printf("Ваше уравнение является линейным, у него 1 корень, x = %f\n", (-freeTerm) / averageCoeff);
	} else{
		if(discriminant < 0) printf("Уравнение не имеет вещественных корней, так как дискриминант Вашего уравнения меньше нуля!\n");
		if (discriminant == 0) printf("Ваше уравнения имеет 1 решение, x = %f\n", (-averageCoeff)/(2*seniorCoeff));
		if (discriminant > 0) printf("Ваше уравнение имеет 2 корня, равные x1 = %f и x2 = %f", ((-averageCoeff)+sqrt(discriminant))/(2*seniorCoeff),((-averageCoeff)-sqrt(discriminant))/(2*seniorCoeff));
	}
	return 0;
}
