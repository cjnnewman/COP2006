// File: mealcalc.cpp
// Class: COP 2006, 202208, 80599
// Who: C. Newman
// Desc: Calculate a meal with price, tax, and tip using console.
// -------------------------------------------------------------

#include <iostream>
#include <iomanip>

// Constants
// -------------------------------------------------------------
const float SALES_TAX_RATE = 0.08;

int main() {

    // Get user input price of the meal
    float mealPrice;
    std::cout << "Price of the meal: ";
    std::cin >> mealPrice;

    // Set precision of output stream to two digits on right side of decimal point
    std::cout << std::fixed << std::setprecision(2);

    // Calculate tax based on pre-defined sales tax of 6.5%
    float salesTax = 0.0;
    salesTax = mealPrice * SALES_TAX_RATE;
    std::cout << "Tax: " << salesTax << std::endl;

    // Calculate meal subtotal
    float subTotal;
    subTotal = mealPrice + salesTax;
    std::cout << "Subtotal: " << subTotal << std::endl;

    // Get user tip as a percentage
    float tipPercentage = 0.0;
    std::cout << "Please enter tip as a percentage (20%): ";
    std::cin >> tipPercentage;

    // Convert user tip into a decimal and output to console
    float tip = subTotal * (tipPercentage / 100.0f);
    std::cout << "Tip: " << tip << std::endl;

    // Calculate total and output to console
    float total = subTotal + tip;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
