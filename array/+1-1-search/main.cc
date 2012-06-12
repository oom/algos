/*
 * TODO: add description
 */
#include "array.h"

#include <ctime>
#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>

ssize_t linear_search( int a[], size_t len, int x )
{
   for( size_t i=0; i<len; ++i )
      if( a[i] == x )
         return i;

   return -1;
}

ssize_t smart_search( int a[], size_t len, int x )
{
   for( size_t i=0; i<len; i+=std::abs(a[i]-x) )
      if( a[i] == x )
         return i;

   return -1;
}

void init( Array & a, int sz )
{
   if( sz <= 0 )
      return;

   a.resize( sz );

   a[ 0 ] = -sz + rand() % (sz * 2 + 1);

   for( int i=1; i<sz; ++i )
   {
      int delta = ( rand() % 2 ) ? 1 : -1;

      a[ i ] = a[ i-1 ] + delta;
   }
}

void test( size_t sz )
{
   Array a;

   init( a, sz );

   for( int i = int(sz) * -2; i <= int(sz) * 2; ++i )
   {
      ssize_t bf = linear_search( &a[0], a.size(), i );
      ssize_t sm = smart_search( &a[0], a.size(), i );

      if( bf != sm )
      {
         std::cout << "Search for " << i << " in " << a << ": " << bf << ' ' << sm << std::endl;
         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for( size_t i=1; i<=10; ++i )
      for( size_t k=0; k<10000; ++k )
         test( 10 );
}
