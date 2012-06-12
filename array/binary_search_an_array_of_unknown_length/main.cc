#include "array.h"

#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <stdexcept>

int bsearch(Array const & a, int x)
{
   int l = 0;
   int u = a.size() - 1;

   while( l <= u )
   {
      int m = l + (u-l) / 2;

      if( a[m] == x )
         return m;

      if( a[m] > x )
         u = m - 1;
      else
         l = m + 1;
   }

   return -1;
}

int bsearchUnknownLength(Array const & a, int x)
{
   int l = 0;
   int u = 1;

   for (;;) {
      try {
         if (a.at(u) >= x)
            break;

         l = u;
         u *= 2;
      }
      catch (std::out_of_range) {
         break;
      }
   }

   while (l <= u) {
      int m = l + (u - l) / 2;

      try {
         if (a.at(m) == x)
            return m;

         if (a.at(m) > x)
            u = m - 1;
         else
            l = m + 1;
      }
      catch (std::out_of_range) {
         u = m - 1;
      }
   }

   return -1;
}

void init( Array & a, size_t size )
{
   a.resize( size );

   for( size_t i=0; i<size; ++i )
   {
      a[ i ] = rand() % (size * 2);
   }

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
