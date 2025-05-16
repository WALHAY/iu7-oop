#pragma once

#include "base/BaseException.hpp"

class NotEqualSize : public BaseException
{
  public:
    NotEqualSize(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid addition/subtraction matrix size")
    {
    }
};

class InitListWrongSize : public BaseException
{
  public:
    InitListWrongSize(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid initializer list dimension")
    {
    }
};

class MatrixRowOutOfBounds : public BaseException
{
  public:
    MatrixRowOutOfBounds(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix row")
    {
    }
};

class MatrixColumnOutOfBounds : public BaseException
{
  public:
    MatrixColumnOutOfBounds(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix column")
    {
    }
};

class InvalidInsertColumn : public BaseException
{
  public:
    InvalidInsertColumn(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix column")
    {
    }
};

class InvalidInsertRow : public BaseException
{
  public:
    InvalidInsertRow(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix column")
    {
    }
};

class NotSquareMatrix : public BaseException
{
  public:
    NotSquareMatrix(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Matrix is not square")
    {
    }
};

class NotInvertible : public BaseException
{
  public:
    NotInvertible(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class MatrixBadAlloc : public BaseException
{
  public:
    MatrixBadAlloc(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class MatrixInvalidSize : public BaseException
{
  public:
    MatrixInvalidSize(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class InsertContainerInvalidSize : public BaseException
{
  public:
    InsertContainerInvalidSize(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class ZeroDeterminant : public BaseException
{
  public:
    ZeroDeterminant(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};
