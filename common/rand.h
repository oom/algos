#ifndef ALGO_RAND_H_INCLUDED
#define ALGO_RAND_H_INCLUDED

#include <cstdlib>

inline int rand_range( int left, int right )
{
   return left + ( rand() % (right - left + 1) );
}

#endif // ALGO_RAND_H_INCLUDED
