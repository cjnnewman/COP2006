// File: einstein.cpp
// Class: COP 2006, 202208, 80599
// Who: C. Newman
// Desc: Allow the user to enter a number, then, through Einstein's
// riddle, output 1089.
// -------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstdlib>

int main() {

    // Declare and get user input for three digit number.
    std::string userNumber;
    std::cout << "Please enter a 3 digit number, where the first and last"
                 " digit differ by more than one: ";
    std::cin >> userNumber;

    // Reverse user inputted number.
    std::string userNumberReverse = userNumber;
    userNumberReverse.front() = userNumber.back();
    userNumberReverse.back() = userNumber.front();
    std::cout << "Your number reversed: " << userNumberReverse << std::endl;

    // Convert user input and reversed string to integer values.
    int userNumberInt = std::stoi(userNumber);
    int userNumberReverseInt = std::stoi(userNumberReverse);

    // Calculate difference of input and reversed input.
    int difference = abs(userNumberInt - userNumberReverseInt);
    std::cout << "Difference of your number and its reverse: " << difference << std::endl;

    // Convert difference of integer values back to string.
    std::string differenceString = std::to_string(difference);

    // Reverse the difference value.
    std::string differenceStringReverse = differenceString;
    differenceStringReverse.front() = differenceString.back();
    differenceStringReverse.back() = differenceString.front();
    std::cout << "Reversed difference: " << differenceStringReverse << std::endl;

    // Convert reversed difference value to integer.
    int differenceReverseInt = std::stoi(differenceStringReverse);

    // Calculate and output the sum of the difference and the reversed
    // difference.
    int sumOfDifferences = difference + differenceReverseInt;
    std::cout << "Sum of difference and its reverse: " << sumOfDifferences << std::endl;

    return 0;


}
