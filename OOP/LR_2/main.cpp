#include "interfaces/Octal.h"
#include <iostream>

using namespace std;

int main() {
  Octal num1 = {1, 2, 3};
  Octal num2("456");
  Octal num3(3, 7);
  Octal num4;
        
  cout << "num1: " << num1.toString() << endl;
  cout << "num2: " << num2.toString() << endl;
  cout << "num3: " << num3.toString() << endl;
  cout << "num4: " << num4.toString() << endl;
        
  Octal sum = num1.add(num2);
  Octal diff = num3.subtract(num1);
        
  cout << "\nArifmethics operations:" << endl;
  cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << endl;
  cout << num3.toString() << " - " << num1.toString() << " = " << diff.toString() << endl;
        
  cout << "\nComparison operations:" << endl;
  cout << num1.toString() << " equally " << num2.toString() << ": " << boolalpha << num1.equals(num2) << endl;
  cout << num1.toString() << " less " << num3.toString() << ": " << num1.lessThan(num3) << endl;
  cout << num3.toString() << " greater " << num1.toString() << ": " << num3.greaterThan(num1) << endl;
        
  cout << "\nAssignment operations:" << endl;
  Octal num5 = num1.copy();
  num5.addAssign(num2);
  cout << num1.toString() << " += " << num2.toString() << " = " << num5.toString() << endl;
        
  Octal num6 = num3.copy();
  num6.subtractAssign(num1);
  cout << num3.toString() << " -= " << num1.toString() << " = " << num6.toString() << endl;

  return 0;
}