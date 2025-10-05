// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

// сначала компиляция gtest-all.cc:       g++ -c ../gtest/gtest-all.cc
// компиляция тестов на матрицы:          g++ -o tests_matrix_without_vectors test_main.cpp test_tmatrix.cpp gtest-all.o  -I../include -I../gtest  -pthread
// компиляций фулл тестов:                g++ -o tests_matrix_full test_main.cpp test_tvector.cpp test_tmatrix.cpp gtest-all.o  -I../include -I../gtest  -pthread
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <assert.h>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -
// шаблонный вектор на динамической памяти
template <typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T *pMem;

public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz >= MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero and would be lower than max");
    pMem = new T[sz](); // {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T *arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector &v)
  {
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = v.pMem[i];
    }
  }
  TDynamicVector(TDynamicVector &&v) noexcept
  {
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    if (pMem != nullptr)
    {
      delete[] pMem;
    }
  }
  TDynamicVector &operator=(const TDynamicVector &v)
  {
    if (*this == v)
    {
      return *this;
    }
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = v.pMem[i];
    }
    return *this;
  }
  TDynamicVector &operator=(TDynamicVector &&v) noexcept
  {

    pMem = nullptr;
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T &operator[](size_t ind)
  {
    if (ind < 0 || ind >= sz)
    {
      throw 1;
    }
    return pMem[ind];
  }
  const T &operator[](size_t ind) const
  {
    if (ind < 0 || ind >= sz)
    {
      throw 2;
    }
    return pMem[ind];
  }
  // индексация с контролем
  T &at(size_t ind)
  {
    if (ind < 0 || ind >= sz)
    {
      throw 2;
    }
    return pMem[ind];
  }
  const T &at(size_t ind) const
  {
    if (ind < 0 || ind >= sz)
    {
      throw 2;
    }
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector &v) const noexcept
  {
    if (sz != v.sz)
    {
      return false;
    }
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i])
      {
        return false;
      }
    }
    return true;
  }
  bool operator!=(const TDynamicVector &v) const noexcept
  {
    return (!(*this == v));
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    for (int i = 0; i < sz; i++)
    {
      pMem[i] += val;
    }
    return *this;
  }
  TDynamicVector operator-(T val)
  {
    for (int i = 0; i < sz; i++)
    {
      pMem[i] -= val;
    }
    return *this;
  }
  TDynamicVector operator*(T val)
  {
    for (int i = 0; i < sz; i++)
    {
      pMem[i] *= val;
    }
    return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector &v)
  {
    if (sz != v.sz)
    {
      throw 3;
    }
    for (int i = 0; i < sz; i++)
    {
      pMem[i] += v.pMem[i];
    }
    return *this;
  }
  TDynamicVector operator-(const TDynamicVector &v)
  {
    if (sz != v.sz)
    {
      throw 3;
    }
    for (int i = 0; i < sz; i++)
    {
      pMem[i] -= v.pMem[i];
    }
    return *this;
  }
  T operator*(const TDynamicVector &v) noexcept(noexcept(T()))
  {
    if (sz != v.sz)
    {
      throw 3;
    }
    T sum = 0;
    for (int i = 0; i < sz; i++)
    {
      sum += pMem[i] * v.pMem[i];
    }
    return sum;
  }

  friend void swap(TDynamicVector &lhs, TDynamicVector &rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream &operator>>(istream &istr, TDynamicVector &v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream &operator<<(ostream &ostr, const TDynamicVector &v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};

// Динамическая матрица -
// шаблонная матрица на динамической памяти
template <typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:
  using TDynamicVector<TDynamicVector<T>>::operator[];
  size_t size() const
  {
    return sz;
  }
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s < 0 || s > sz || s >= MAX_MATRIX_SIZE)
    {
      throw 1;
    }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  // сравнение
  bool operator==(const TDynamicMatrix &m) const noexcept
  {
    if (sz != m.sz)
    {
      return false;
    }
    for (int i = 0; i < sz; i++)
    {
      for (int j = 0; j < sz; j++)
      {
        if (pMem[i][j] != m.pMem[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T &val)
  {
    for (int i = 0; i < sz; i++)
    {
      for (int j = 0; j < sz; j++)
      {
        pMem[i] = pMem[i] * val;
      }
    }
    return *this;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T> &v)
  {
    if (sz != v.sz)
    {
      throw 4;
    }
    TDynamicVector<T> a(sz);

    for (int i = 0; i < sz; i++)
    {
      T sum = 0;
      for (int j = 0; j < sz; j++)
      {

        sum += (*this)[i][j] * v[j];
      }
      a[i] = sum;
    }
    return a;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix &m)
  {
    if (sz != m.sz)
    {
      throw 5;
    }
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = pMem[i] + m.pMem[i];
    }
    return *this;
  }

  TDynamicMatrix operator-(const TDynamicMatrix &m)
  {

    if (sz != m.sz)
    {
      throw 6;
    }
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = pMem[i] - m.pMem[i];
    }
    return *this;
  }
  TDynamicMatrix operator*(const TDynamicMatrix &m)
  {
    if (sz != m.sz)
    {
      throw 7;
    }
    TDynamicMatrix<T> a(sz);
    for (int i = 0; i < sz; i++)
    {
      for (int j = 0; j < sz; j++)
      {
        T sum = 0;
        for (int k = 0; k < sz; k++)
        {
          sum += pMem[i][k] * m.pMem[k][j];
        }
        a[i][j] = sum;
      }
    }
    return a;
  }

  // ввод/вывод
  friend istream &
  operator>>(istream &istr, TDynamicMatrix &v)
  {
    for (int i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream &operator<<(ostream &ostr, const TDynamicMatrix &v)
  {
    for (int i = 0; i < v.sz; i++)
    {
      for (int j = 0; j < v.sz; j++)
      {
        ostr << v.pMem[i][j] << ' ';
      }
      ostr << endl;
    }
    return ostr;
  }
};

#endif
