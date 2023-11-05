#include "./include/error.hpp"
#include <string>
#include <iostream>
#include "error.hpp"

using namespace std;

void Error::printError(std::string typeOfError, std::string lineInError)
{
    cout << typeOfError << " in " << lineInError << endl;
}