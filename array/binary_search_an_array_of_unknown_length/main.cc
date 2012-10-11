#include "array.h"

#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <stdexcept>

int bsearch( Array const & a, int x )
{
   int lo = 0;
   int hi = a.size() - 1;

   while( lo <= hi )
   {
      int mid = lo + (hi - lo) / 2;

      if( a[mid] == x )
         return mid;

      if( a[mid] > x )
         hi = mid - 1;
      else
         lo = mid + 1;
   }

   return -1;
}

int const * at( Array const & a, int idx )
{
   try
   {
      return &a.at(idx);
   }
   catch (std::out_of_range)
   {
      return 0;
   }
}

int bsearchUnknownLength( Array const & a, int x )
{
   int lo = 0;
   int hi = 1;

   for( ;; )
   {
      int const * p = at( a, hi );

      if( p == 0 || *p >= x )
         break;

      lo = hi;
      hi *= 2;
   }

   while( lo <= hi )
   {
      int mid = lo + (hi - lo) / 2;
      int const * p = at( a, mid );

      if( p == 0 || *p > x )
         hi = mid - 1;
      else if( *p < x )
         lo = mid + 1;
      else
         return mid;
   }

   return -1;
}

void init( Array & a, size_t size )
{
   a.resize( size );

   for( size_t i=0; i<size; ++i )
      a[ i ] = rand() % (size * 2);

   std::sort( a.begin(), a.end() );
}

void test( int size )
{
   Array a;

   init( a, size );

   for( int i=-1; i<=size*2; ++i )
   {
      int bf = bsearch( a, i );
      int sm = bsearchUnknownLength( a, i );

      if( bf < 0 && sm >= 0 )
      {
         std::cout << a << ": x=" << i << " bf=" << bf << " sm=" << sm << std::endl;
         abort();
      }
      else if( sm < 0 && bf >= 0 )
      {
         std::cout << a << ": x=" << i << " bf=" << bf << " sm=" << sm << std::endl;
         abort();
      }
      else if( bf != sm && a[bf] != a[sm] )
      {
         std::cout << a << ": x=" << i << " bf=" << bf << " sm=" << sm << std::endl;
         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for( size_t i=0; i<10; ++i )
   {
      for( size_t k=0; k<10000; ++k )
         test( i );
   }
}
