#include <iostream>
#include <iomanip>
#include "complex.h"

using namespace std;

void printSection(const string &title)
{
    cout << "\n"
         << string(50, '=') << endl;
    cout << title << endl;
    cout << string(50, '=') << endl;
}

int main()
{
    try
    {
        printSection("CONSTRUCTOR TESTING");
        Complex c1(3, 4);
        Complex c2(1, 2);
        Complex c3;
        cout << "c1 = " << c1 << endl;
        cout << "c2 = " << c2 << endl;
        cout << "c3 = " << c3 << endl;

        printSection("BINARY ARITHMETIC");
        cout << "c1 + c2 = " << (c1 + c2) << endl;
        cout << "c1 - c2 = " << (c1 - c2) << endl;
        cout << "c1 * c2 = " << (c1 * c2) << endl;
        cout << "c1 / c2 = " << (c1 / c2) << endl;

        printSection("OPERATIONS WITH NUMBERS");
        cout << "c1 + 5 = " << (c1 + 5) << endl;
        cout << "5 + c1 = " << (5 + c1) << endl;
        cout << "c1 - 2 = " << (c1 - 2) << endl;
        cout << "10 - c1 = " << (10 - c1) << endl;
        cout << "c1 * 2 = " << (c1 * 2) << endl;
        cout << "2 * c1 = " << (2 * c1) << endl;
        cout << "c1 / 2 = " << (c1 / 2) << endl;
        cout << "10 / c2 = " << (10 / c2) << endl;

        printSection("COMPOUND ASSIGNMENT");
        Complex c12 = c1;
        cout << "c12 initial: " << c12 << endl;
        c12 += c2;
        cout << "c12 += c2: " << c12 << endl;
        c12 -= c2;
        cout << "c12 -= c2: " << c12 << endl;
        c12 *= Complex(2, 0);
        cout << "c12 *= 2: " << c12 << endl;
        c12 /= Complex(2, 0);
        cout << "c12 /= 2: " << c12 << endl;

        printSection("UNARY OPERATORS");
        cout << "-c1 = " << (-c1) << endl;
        cout << "+c1 = " << (+c1) << endl;

        Complex c15 = c1;
        cout << "Before ++c15: " << c15 << endl;
        ++c15;
        cout << "After ++c15: " << c15 << endl;

        Complex c16 = c1;
        cout << "Before c16++: " << c16 << endl;
        Complex c17 = c16++;
        cout << "After c16++, c16: " << c16 << ", returned: " << c17 << endl;

        Complex c18 = c1;
        cout << "Before --c18: " << c18 << endl;
        --c18;
        cout << "After --c18: " << c18 << endl;

        printSection("COMPARISON OPERATORS");
        cout << boolalpha; // Print true/false instead of 1/0
        cout << "c1 == c2: " << (c1 == c2) << endl;
        cout << "c1 != c2: " << (c1 != c2) << endl;
        cout << "c1 < c2: " << (c1 < c2) << endl;
        cout << "c1 > c2: " << (c1 > c2) << endl;
        cout << "c1 <= c2: " << (c1 <= c2) << endl;
        cout << "c1 >= c2: " << (c1 >= c2) << endl;

        Complex c19(3, 4);
        cout << "c1 == Complex(3,4): " << (c1 == c19) << endl;

        printSection("STREAM I/O");
        Complex zero(0, 0);
        cout << "c1 using <<: " << c1 << endl;

        // Uncomment to test input:
        
        Complex c20;
        cout << "Enter a complex number:" << endl;
        cin >> c20;
        cout << "You entered: " << c20 << endl;
        

        printSection("HELPER METHODS");
        cout << fixed << setprecision(4);
        cout << "c1.getMagnitude(): " << c1.getMagnitude() << endl;

        cout << "c1.getReal(): " << c1.getReal() << endl;
        cout << "c1.getImag(): " << c1.getImag() << endl;

        Complex c21;
        c21.setReal(5);
        c21.setImag(-3);
        cout << "After setReal(5) and setImag(-3): " << c21 << endl;

        printSection("DISPLAY METHOD");
        cout << "Using display(): ";
        c1.display();

        printSection("DIVISION BY ZERO TEST");
        try
        {
            Complex result = c1 / zero;
            cout << "Result: " << result << endl;
        }
        catch (const runtime_error &e)
        {
            cout << "Exception caught: " << e.what() << endl;
        }

       
        

        printSection("END OF TESTING");
       
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        return 1;
    }

    return 0;
}