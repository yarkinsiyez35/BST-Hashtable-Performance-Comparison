#include "Exception.h"

Exception::Exception()  //default constructor
{
    message = "Exception occurred!";
}

Exception::Exception(const string &msg) //parametric constructor
{
    message = msg;
}

const string & Exception::getMessage()  //returns the message
{
    return message;
}

void Exception::setMessage(const std::string &msg)  //sets the message
{
    message = msg;
}