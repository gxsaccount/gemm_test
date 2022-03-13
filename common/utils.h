#include <stdio.h>
#include <vector>
#include <cmath>
#include <sys/time.h>
#include <time.h>

extern double drand48();
static  double gtod_ref_time_sec = 0.0;  

template <class DTYPE>
class Matrix
{
  std::vector<size_t> m_shape;
  std::vector<DTYPE> m_data;

public:
  const std::vector<size_t> &shape()
  {
    return m_shape;
  }
  const std::vector<DTYPE> &data()
  {
    return m_data;
  }
  size_t len()
  {
    size_t len = 1;
    for (auto num : m_shape)
    {
      len *= num;
    }
    return len;
  };
  Matrix(const std::vector<DTYPE> data, const std::vector<size_t> shape)
  {
    static_assert(std::is_arithmetic<DTYPE>::value != 0, "Must be arithmetic type");
    size_t len = 1;
    for (auto num : m_shape)
    {
      len *= num;
    }
    static_assert(len == data.size());
    this->m_data = data;
    this->m_len = shape;
  };
};

template <class DTYPE>
DTYPE distance_l1(const Matrix<DTYPE> &m1, const Matrix<DTYPE> &m2)
{
  static_assert(std::is_arithmetic<DTYPE>::value != 0, "Must be arithmetic type");
  static_assert(m1.shape().size() == m2.shape().size());
  for (size_t i = 0; i < m1.shape().size(); ++i)
  {
    static_assert(m1[i] == m2[i]);
  }
  DTYPE diff = (DTYPE)0;
  for (size_t i = 0; i < m1.data().size(); ++i)
  {
    diff += std::abs(m1.data()[i] - m2.data()[i]);
  }
  return diff;
}

template <class DTYPE>
Matrix<DTYPE> &random_matrix(const std::vector<size_t> &shape)
{
  size_t len = 1;
  for (auto num : shape)
  {
    len *= num;
  }
  std::vector<DTYPE> data(len);
  for (size_t i = 0; i < len; ++i)
  {
    data[i] = (DTYPE)drand48();
  }
  Matrix<DTYPE> matrix(data, shape);
  return matrix;
}



/* Adapted from the bl2_clock() routine in the BLIS library */

double dclock()
{
  double the_time, norm_sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);

  if (gtod_ref_time_sec == 0.0)
    gtod_ref_time_sec = (double)tv.tv_sec;

  norm_sec = (double)tv.tv_sec - gtod_ref_time_sec;

  the_time = norm_sec + tv.tv_usec * 1.0e-6;

  return the_time;
}