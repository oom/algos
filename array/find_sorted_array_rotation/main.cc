#include "array.h"

// Works with no duplicates only
int findSortedArrayRotation( Array const & a )
{
   if( a.empty() )
      return -1;

   int lo = 0;
   int hi = a.size() - 1;

   while( a[lo] > a[hi] )
   {
      int mid = lo + (hi - lo) / 2;

      if( a[mid] > a[hi] )
         lo = mid + 1;
      else
         hi = mid;
   }

   return lo;
}

// -- TEST --
#include "rand.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

int findSortedArrayRotationLinear( Array const & a )
{
   if( a.empty() )
      return -1;

   int ret = 0;
   int min = a[ 0 ];

   for( size_t i = 1; i < a.size(); ++i )
      if( min > a[ i ] )
      {
         min = a[ i ];
         ret = i;
      }

   return ret;
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   for( size_t i = 0; i < sz; ++i )
      a[ i ] = i;
}

void test_empty()
{
   int pos = findSortedArrayRotation( Array() );

   if( pos != -1 )
   {
      std::cout << "empty array: expected=-1 actual=" << pos << std::endl;
      abort();
   }
}

void test( int sz )
{
   Array a;

   init( a, sz );

   for( int i = 0; i < sz; ++i )
   {
      int x = findSortedArrayRotation( a );
      int y = findSortedArrayRotationLinear( a );

      if( x != y )
      {
         std::cout << a << std::endl;
         std::cout << "expected=" << y << " actual=" << x << std::endl;
         abort();
      }

      std::rotate( a.begin(), a.begin() + a.size() - 1, a.end() );
   }
}

int main()
{
   test_empty();

   for( int sz = 1; sz < 100; ++sz )
      test( sz );
}
