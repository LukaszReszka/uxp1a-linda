#pragma once
#include <exception>

enum MutexExceptionType {
  CANT_INIT_ATTRIBUTES,
  CANT_SET_ATTRIBUTES,
  CANT_DESTROY_ATTRIBUTES,
  CANT_DESTROY_MUTEX,
  LOCK_ERROR,
  UNLOCK_ERROR,
  CANT_INIT_MUTEX
};

class MutexException : public std::exception {
 public:
  explicit MutexException(MutexExceptionType exceptionType);

  virtual const char* what() const noexcept;

  virtual ~MutexException() = default;

 private:
  MutexExceptionType type;
};