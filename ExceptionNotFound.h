#ifndef __EXCEPTION_NOT_FOUND_H_INCLUED__
#define __EXCEPTION_NOT_FOUND_H_INCLUED__

#include <exception>


class ExceptionNotFound : public std::exception {
public:
  explicit ExceptionNotFound(const std::string& message) 
    : m_message(message) {
  }

  virtual ~ExceptionNotFound() throw() { }

  virtual const char* what() const throw() {
    return m_message.c_str();
  }

private:
  std::string m_message;
};


#endif
