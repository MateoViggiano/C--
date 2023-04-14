#include <iostream>
#include <cmath>

using namespace std;

double ln(double x) {
  double sum = 0.0;
  double term = (x - 1) / x;
  int i = 1;
  while (term != 0.0) {
    sum += term;
    term = ((x - 1) / x) * pow(-1, i) / i;
    x += 1.0;
    i += 1;
  }
  return sum;
}

double dln(double x) {
  return 1 / x;
}

double newton_raphson_ln(double x, double tol, int max_iter) {
  double fx = ln(x);
  double dfx = dln(x);
  int iter = 0;
  while (iter < max_iter && abs(fx) > tol) {
    x = x - fx / dfx;
    fx = ln(x);
    dfx = dln(x);
    iter++;
  }
  return x;
}

int main() {
  double x = 2346234; // número alto
  double tol = 1e-3; // tolerancia
  int max_iter = 1000; // número máximo de iteraciones
  double result = newton_raphson_ln(x, tol, max_iter);
  cout << "ln(" << x << ") = " << result << endl;
  return 0;
}