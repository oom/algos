#include "array.h"

#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include <vector>
#include <iostream>
#include <algorithm>

int dumb( Array const & a, Array const & b, size_t k )
{
   if( k >= a.size() + b.size() )
      return INT_MIN;

   Array u(a);

   u.insert( u.end(), b.begin(), b.end() );
   std::sort( u.begin(), u.end() );

   return u[k];
}

int better( Array const & a, Array const & b, size_t k )
{
   size_t i = 0;
   size_t j = 0;

   while( i < a.size() && j < b.size() )
   {
      int val;

      if( a[i] < b[j] )
         val = a[i++];
      else
        val = b[j++];

      if( k-- == 0 )
         return val;
   }

   if( i+k < a.size() )
      return a[i+k];

   if( j+k < b.size() )
      return b[j+k];

   return INT_MIN;
}

int best( Array const & a, Array const & b, size_t k )
{
   if( k >= a.size() + b.size() )
      return INT_MIN;

   size_t count = k + 1;

   // Consider `count' smallest elements coming from the union of a and b.
   // acnt of them come from the first array, bcnt=count-acnt come from the second.

   // We are trying to determine how many elements come from the first array.
   // This number is within the following range inclusive:
   size_t begin = std::max<int>(0, count - b.size());
   size_t end   = std::min(a.size(), count);

   // Use binary search to find how many elements come from the first array.
   while( begin < end )
   {
      // Consider the case when acnt elements come from the first array, bcnt come from the second one.
      size_t acnt = begin + (end - begin) / 2;
      size_t bcnt = count - acnt;

      if( acnt < a.size() && bcnt > 0 && a[acnt] < b[bcnt-1] )
      {
         // Take more elements from the first array.
         begin = acnt + 1;
      }
      else if( acnt > 0 && bcnt < b.size() && a[acnt-1] > b[bcnt] )
      {
         // Take more elements from the second array.
         end = acnt - 1;
      }
      else
      {
         begin = acnt;
         break;
      }
   }

   if( begin == 0 )
      return b[count-1]; // all elements from b[]

   if( begin == count )
      return a[count-1]; // all elements from a[]

   return std::max(a[begin-1], b[count-begin-1]);
}

void init( Array & a, size_t sz )
{
   a.resize(sz);

   size_t mod = sz * 2 + 1;

   for( size_t i=0; i<sz; ++i )
      a[i] = rand() % mod;

   std::sort( a.begin(), a.end() );
}

void test( size_t sz )
{
   Array a, b;

   init( a, rand() % (sz+1) );
   init( b, rand() % (sz+1) );

   for( size_t i=0; i<=sz*2+1; ++i )
   {
      int x = dumb(a, b, i);
      int y = better(a, b, i);
      int z = best(a, b, i);

      if( x != y || x != z )
      {
         std::cout << "A: " << a << "\nB: " << b << "\nk=" << i << " x=" << x << " y=" << y << " z=" << z << std::endl;
         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz=0; sz<10; ++sz )
      for( int j=0; j<1000000; ++j )
         test(sz);
}
