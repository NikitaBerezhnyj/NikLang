#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

class Error {
public:
    void printError(std::string typeOfError, std::string lineInError);
};

#endif // ERROR_H