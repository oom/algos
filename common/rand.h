#ifndef ALGO_RAND_H_INCLUDED
#define ALGO_RAND_H_INCLUDED

#include "array.h"
#include <cstdlib>

inline int rand_range( int left, int right )
{
   return left + ( rand() % (right - left + 1) );
}

class RandUnique
{
public:
   RandUnique( int left, int right );

   int operator()();

private:
   size_t m_size;
   Array  m_array;
};

#endif // ALGO_RAND_H_INCLUDED
