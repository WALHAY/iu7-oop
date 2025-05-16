#pragma once

#include "base/BaseException.hpp"

class MatricesNotEqualSize : public BaseException
{
  public:
    MatricesNotEqualSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid addition/subtraction matrix size")
    {
    }
};

class InitListInvalidSize : public BaseException
{
  public:
    InitListInvalidSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid initializer list shape")
    {
    }
};

class MatrixRowOutOfBounds : public BaseException
{
  public:
    MatrixRowOutOfBounds(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid matrix row access")
    {
    }
};

class MatrixColumnOutOfBounds : public BaseException
{
  public:
    MatrixColumnOutOfBounds(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid matrix column access")
    {
    }
};

class InvalidInsertColumn : public BaseException
{
  public:
    InvalidInsertColumn(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid matrix column insertion")
    {
    }
};

class InvalidInsertRow : public BaseException
{
  public:
    InvalidInsertRow(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid matrix column insertion")
    {
    }
};

class DeterminantNotSquareMatrix : public BaseException
{
  public:
    DeterminantNotSquareMatrix(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Determinant require square matrix")
    {
    }
};

class NotInvertible : public BaseException
{
  public:
    NotInvertible(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Matrix is not invertible")
    {
    }
};

class MatrixBadAlloc : public BaseException
{
  public:
    MatrixBadAlloc(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Failed to allocate memory for matrix")
    {
    }
};

class MatrixInvalidShape : public BaseException
{
  public:
    MatrixInvalidShape(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Invalid matrix shape")
    {
    }
};

class InsertContainerInvalidSize : public BaseException
{
  public:
    InsertContainerInvalidSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Wrong iterable size on insertion")
    {
    }
};

class DivisionZeroDeterminant : public BaseException
{
  public:
    DivisionZeroDeterminant(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Trying to invert matrix with zero determinant")
    {
    }
};
