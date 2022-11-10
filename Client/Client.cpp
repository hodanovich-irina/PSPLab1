#include <iostream>
#include <cmath>
#include <cstdlib>
#include "ClientTCP.h"

double function(double x) {
	return pow(x, 3) *  sin(x);
}

double method_simpson(double b, double a, double y1) {

	int n = 2;
	double h = (b - a) / n;	// вычисляем шаг - h
	double sum = 0;		// сумма, результат вычисления интеграла.
	double x0 = a;		// правая граница подотрезка отрезка [a, b]
	double x1 = a + h;	// левая граница подотрезка отрезка [a, b]

	for (int i = 0; i < n; i++) // в цикле применяем формулу Симпсона
	{
		sum += function(x0) + 4 * function(x0 + h / 2) + function(x1);	//для каждого подотрезка, и складываем все полученные значения в общую сумму.
		x0 += h;	// сдвигаем левую и
		x1 += h;	// правую границу, иначе говоря меняем подотрезок отрезка [a, b]
	}

	return (h / 6) * sum;	// возвращаем сумму умноженную на (h/6)(по формуле), т.к. (h/6) общий множитель который можно вынести за скобки.
}

int main()
{
	std::string message;
	double x1, x2, y1;
	double result = 0;

	ClientTCP client(1000);
	message = client.receiveMessage(15);

	x1 = atof(message.substr(0, message.find(' ')).c_str());
	x2 = atof(message.substr(message.find(' ') + 1, message.length() - message.find(' ') - 1).c_str());
	y1 = function(x1);

	std::cout << "A: " << x1 << std::endl;
	std::cout << "B: " << x2 << std::endl;
	std::cout << "Y: " << y1 << std::endl;
	
	result = method_simpson(x1, x2, y1);

	std::cout << "result: " << result << std::endl;

	client.sendMessage(std::to_string(result));

	int tmp = getchar();

	return 0;
}

