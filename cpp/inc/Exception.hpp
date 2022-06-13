#pragma once
/* std */
#include <stdexcept>
#include <string>

class Exception : public std::exception {
  private:
    /* Members */
    std::string _message;

  public:
    /* Constructors */
    Exception(std::string &&message) : _message(message) {}
    virtual ~Exception() throw() {}
    /* Methods */
    virtual const char* what() const throw() { return this->_message.c_str(); }
};
