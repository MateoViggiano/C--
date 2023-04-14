#include <iostream>
#include<math.h>
using namespace std;

double power(double base, double exponent) {
   // Calcular la potencia fraccionaria utilizando la fórmula
   double result = exp(exponent * log(base));
   return result;
}

int main() {
   // Leer la base y el exponente fraccionario
   double base, exponent;
   cout << "Ingrese la base: ";
   cin >> base;
   cout << "Ingrese el exponente fraccionario: ";
   cin >> exponent;

   // Calcular y mostrar la potencia fraccionaria
   double result = power(base, exponent);
   cout << base << "^" << exponent << " = " << result << endl;

   return 0;
}