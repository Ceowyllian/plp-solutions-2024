#include <iostream>
#include <string>
#include "complex.h"

int main()
{
	Complex acc{ 0,0 };
	while (true) {

		double real, imag;
		Complex operand{ 0,0 };
		std::string result;

		system("cls");
		printf("Accumulator value: %s\n", acc.toString().c_str());
		puts("Operations: +, -, *, / , ~, A(Arg), M(Module).");
		std::cout << "Enter operation: ";

		char operation;
		std::cin >> operation;
		switch (operation)
		{
		case '+':
			std::cout << "Enter real part: ";
			std::cin >> real;
			std::cout << "Enter imag part: ";
			std::cin >> imag;
			operand = Complex(real, imag);
			acc = acc + operand;
			result = acc.toString();
			break;
		case '-':
			std::cout << "Enter real part: ";
			std::cin >> real;
			std::cout << "Enter imag part: ";
			std::cin >> imag;
			operand = Complex(real, imag);
			acc = acc - operand;
			result = acc.toString();
			break;
		case '*':
			std::cout << "Enter real part: ";
			std::cin >> real;
			std::cout << "Enter imag part: ";
			std::cin >> imag;
			operand = Complex(real, imag);
			acc = acc * operand;
			result = acc.toString();
			break;
		case '/':
			std::cout << "Enter real part: ";
			std::cin >> real;
			std::cout << "Enter imag part: ";
			std::cin >> imag;
			operand = Complex(real, imag);
			acc = acc / operand;
			result = acc.toString();
			break;
		case '~':
			acc = -acc;
			result = acc.toString();
			break;
		case 'A':
			result = std::to_string(acc.Arg());
			break;
		case 'M':
			result = std::to_string(acc.Mod());
			break;
		case 'Q':
			exit(0);
		default:
			throw new std::exception("Invalid operation");
		}
		std::cout << "result: " << result << "\n";
		system("pause");
	}
}
