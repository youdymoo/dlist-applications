#include <iostream>
#include <cstdlib>
#include <sstream>
#include "dlist.h"

class Complex {
private:
    int re;
    int im;

public:
    Complex(int realPart = 0, int imaginaryPart = 0) {
        re = realPart;
        im = imaginaryPart;
    }

    Complex(const Complex &c) {
        re = c.re;
        im = c.im;
    }

    friend Complex *complexPlus(Complex *a, Complex *b);
    friend Complex *complexMinus(Complex *a, Complex *b);
    friend Complex *complexTimes(Complex *a, Complex *b);
    friend Complex *complexNegate(Complex *a);

    void print() {
        if (re == 0)
            cout << "0";
        else
            cout << re;

        if (im == 0)
            cout << "+0";
        else {
            if (im > 0)
                cout << "+" << im;
            else
                cout << im;
        }
        cout << "i";
    }

};

class badInput {
    // OVERVIEW: an exception class
};

Complex *complexPlus(Complex *a, Complex *b) {
    Complex *result = new Complex();
    result->re = a->re + b->re;
    result->im = a->im + b->im;
    return result;
}

Complex *complexMinus(Complex *a, Complex *b) {
    Complex *result = new Complex();
    result->re = a->re - b->re;
    result->im = a->im - b->im;
    return result;
}

Complex *complexTimes(Complex *a, Complex *b) {
    Complex *result = new Complex();
    result->re = a->re * b->re - a->im * b->im;
    result->im = a->re * b->im + a->im * b->re;
    return result;
}

Complex *complexNegate(Complex *a) {
    Complex *result = new Complex();
    result->re = - a->re;
    result->im = - a->im;
    return result;
}

const string opName[] = {"+", "-", "*", "n", "d", "r", "p", "c", "a", "q"};

int opInput(string &input) {
    string op;
    op = input.at(0);
    int size = input.size();

    if (size == 1) {
        for (int i = 0; i < 10; i++) {
            if (op == opName[i]) {
                return i;
            }
        }
        badInput e;
        throw e;
    }
    else if (op == "+") {
        badInput e;
        throw e;
    }
    else
        return 10;
}

Complex *initComplex(string &num) {
    if (num.at(0) == '+') {
	badInput e;
	throw e;
    }

    istringstream num_helper(num);
    int realPart, imaginaryPart;
    string i;
    num_helper >> realPart >> imaginaryPart >> i;

    if (num_helper.bad() || i != "i") {
        badInput e;
        throw e;
    }

    Complex *complex = new Complex(realPart, imaginaryPart);
    return complex;
}

int main() {
    Dlist<Complex> stack;
    string input;
    int op;

    while (op != 9) {
        cin >> input;

        try {
            op = opInput(input);
            switch (op) {
                case 0: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        stack.insertFront(a);
                        break;
                    }
                    Complex *b = stack.removeFront();
                    Complex *result = complexPlus(a, b);
                    stack.insertFront(result);
                    delete a;
                    delete b;
                    break;
                }

                case 1: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        stack.insertFront(a);
                        break;
                    }
                    Complex *b = stack.removeFront();
                    Complex *result = complexMinus(b, a);
                    stack.insertFront(result);
                    delete a;
                    delete b;
                    break;
                }

                case 2: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        stack.insertFront(a);
                        break;
                    }
                    Complex *b = stack.removeFront();
                    Complex *result = complexTimes(a, b);
                    stack.insertFront(result);
                    delete a;
                    delete b;
                    break;
                }

                case 3: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    /*Complex *b = new Complex(-1, 0);
                    a = complexTimes(a, b);
                    stack.insertFront(a);
                    delete b;*/
                    Complex *result = complexNegate(a);
                    stack.insertFront(result);
                    delete a;
                    break;
                }

                case 4: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    Complex *b = new Complex(*a);
                    stack.insertFront(a);
                    stack.insertFront(b);
                    break;
                }

                case 5: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        stack.insertFront(a);
                        break;
                    }
                    Complex *b = stack.removeFront();
                    stack.insertFront(a);
                    stack.insertFront(b);
                    break;
                }

                case 6: {
                    if (stack.isEmpty()) {
                        cout << "Not enough operands" << endl;
                        break;
                    }
                    Complex *a = stack.removeFront();
                    a->print();
                    cout << endl;
                    stack.insertFront(a);
                    break;
                }

                case 7: {
                    Dlist<Complex> temp;
                    stack = temp;
                    break;
                }

                case 8: {
                    if (stack.isEmpty()) {
                        cout << endl;
                    }
                    else {
                        Dlist<Complex> temp;
                        temp = stack;
                        while (!temp.isEmpty()) {
                            Complex *a = temp.removeFront();
                            a->print();
                            cout << " ";
                            delete a;
                        }
                        cout << endl;
                    }
                    break;
                }

                case 9: {
                    break;
                }

                case 10: {
                    Complex *number = initComplex(input);
                    stack.insertFront(number);
                    break;
                }
            }
        }

        catch (badInput) {
                cout << "Bad input" << endl;
            }
    }
    return 0;
}