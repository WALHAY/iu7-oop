#pragma once

#include "exceptions/BaseException.hpp"
#include <ctime>

class MatricesNotEqualSize : public BaseException
{
  public:
    MatricesNotEqualSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class InitListInvalidSize : public BaseException
{
  public:
    InitListInvalidSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class MatrixRowOutOfBounds : public BaseException
{
  public:
    MatrixRowOutOfBounds(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class MatrixColumnOutOfBounds : public BaseException
{
  public:
    MatrixColumnOutOfBounds(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class InvalidInsertColumn : public BaseException
{
  public:
    InvalidInsertColumn(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class InvalidInsertRow : public BaseException
{
  public:
    InvalidInsertRow(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class DeterminantNotSquareMatrix : public BaseException
{
  public:
    DeterminantNotSquareMatrix(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class NotInvertible : public BaseException
{
  public:
    NotInvertible(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class MatrixBadAlloc : public BaseException
{
  public:
    MatrixBadAlloc(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class MatrixInvalidShape : public BaseException
{
  public:
    MatrixInvalidShape(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class InsertContainerInvalidSize : public BaseException
{
  public:
    InsertContainerInvalidSize(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class DivisionZeroDeterminant : public BaseException
{
  public:
    DivisionZeroDeterminant(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};
