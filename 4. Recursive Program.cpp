/*
 * Program: Recursive programs in C++
 *   (a) Sum of the first N natural numbers
 *   (b) Factorial of a number
 *   (c) Nth term of the Fibonacci series
 *   (d) Generate N terms of the Fibonacci series
 *
 * What I understand about recursion:
 *   A recursive function is a function that calls itself. Every recursive
 *   function needs two things:
 *     1. a BASE CASE      - a simple case that stops the calls, and
 *     2. a RECURSIVE CASE - where the function calls itself with a smaller
 *                           problem so that it moves towards the base case.
 *   Without a base case the function would call itself forever (stack overflow).
 *
 * Fibonacci convention I used: F(0) = 0, F(1) = 1, so the series is
 *   0, 1, 1, 2, 3, 5, 8, 13 ...
 */

#include <iostream>
using namespace std;

/* ---------------------------------------------------------------
 * (a) Sum of the first N natural numbers
 *     sum(N) = N + sum(N-1)
 *     Base case: sum(0) = 0
 *     Example: sum(4) = 4 + sum(3) = 4 + 3 + sum(2) = ... = 10
 * --------------------------------------------------------------- */
long long sumNatural(int n) {
    if (n <= 0) {                 // base case: nothing left to add
        return 0;
    }
    return n + sumNatural(n - 1); // recursive case: n plus the sum of the rest
}

/* ---------------------------------------------------------------
 * (b) Factorial of a number
 *     n! = n x (n-1)!
 *     Base case: 0! = 1 and 1! = 1
 *     Example: 4! = 4 x 3! = 4 x 3 x 2! = 4 x 3 x 2 x 1 = 24
 *     I used unsigned long long, which can hold up to 20! only.
 * --------------------------------------------------------------- */
unsigned long long factorial(int n) {
    if (n <= 1) {                 // base case: 0! and 1! are both 1
        return 1;
    }
    return n * factorial(n - 1);  // recursive case
}

/* ---------------------------------------------------------------
 * (c) Nth term of the Fibonacci series
 *     F(n) = F(n-1) + F(n-2)
 *     Base cases: F(0) = 0 and F(1) = 1
 *     Each term is the sum of the two terms before it.
 *     Note: this version calls itself twice, so it gets slow for big n
 *     (about 2^n calls). It is fine for small values like n <= 40.
 * --------------------------------------------------------------- */
long long fibonacci(int n) {
    if (n == 0) return 0;         // first base case
    if (n == 1) return 1;         // second base case
    return fibonacci(n - 1) + fibonacci(n - 2);   // recursive case
}

/* ---------------------------------------------------------------
 * (d) Generate N terms of the Fibonacci series
 *     I pass the two current terms (a and b) along in the function, and
 *     "remaining" tells me how many terms are still left to print.
 *     Each call prints a, then calls itself with (b, a+b) and one less
 *     term remaining.
 *     Base case: remaining == 0, so there is nothing more to print.
 *     This is faster than calling fibonacci(i) for each term because every
 *     term is worked out only once.
 * --------------------------------------------------------------- */
void generateFibonacci(int remaining, long long a, long long b) {
    if (remaining <= 0) {         // base case: all terms printed
        return;
    }
    cout << a << " ";                               // print current term
    generateFibonacci(remaining - 1, b, a + b);     // move to the next term
}

/* ---------------------------------------------------------------
 * main: simple menu so I can test each part
 * --------------------------------------------------------------- */
int main() {
    int choice, n;

    do {
        cout << "\n===== RECURSION MENU =====" << endl;
        cout << "1. Sum of first N natural numbers" << endl;
        cout << "2. Factorial of a number" << endl;
        cout << "3. Nth term of Fibonacci series" << endl;
        cout << "4. Generate N terms of Fibonacci series" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) break;      // stop if input is not a number

        switch (choice) {
        case 1:
            cout << "Enter N: ";
            cin >> n;
            if (n < 0) {
                cout << "N must not be negative." << endl;
            } else {
                cout << "Sum of first " << n << " natural numbers = "
                     << sumNatural(n) << endl;
            }
            break;

        case 2:
            cout << "Enter a number (0 to 20): ";
            cin >> n;
            if (n < 0 || n > 20) {
                cout << "Please enter a number between 0 and 20." << endl;
            } else {
                cout << n << "! = " << factorial(n) << endl;
            }
            break;

        case 3:
            cout << "Enter N (0 to 40): ";
            cin >> n;
            if (n < 0 || n > 40) {
                cout << "Please enter a number between 0 and 40." << endl;
            } else {
                cout << "Fibonacci term F(" << n << ") = " << fibonacci(n) << endl;
            }
            break;

        case 4:
            cout << "Enter number of terms: ";
            cin >> n;
            if (n <= 0) {
                cout << "Number of terms must be at least 1." << endl;
            } else {
                cout << "First " << n << " terms: ";
                generateFibonacci(n, 0, 1);   // series starts with 0 and 1
                cout << endl;
            }
            break;

        case 5:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 5);

    return 0;
}