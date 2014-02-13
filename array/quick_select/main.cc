#include "array.h"
#include <stdlib.h>

size_t partition( Array & a, size_t lo, size_t hi, size_t p )
{
   std::swap( a[hi], a[p] );

   size_t s = lo;
   for( size_t i = lo; i < hi; ++i )
      if( a[i] < a[hi] )
         std::swap( a[s++], a[i] );

   std::swap( a[s], a[hi] );
   return s;
}

int * quickselect( Array & a, size_t k )
{
   if( a.empty() || k >= a.size() )
      return 0;

   size_t lo = 0;
   size_t hi = a.size() - 1;

   while( lo <= hi )
   {
      size_t p = partition(a, lo, hi, lo + rand() % (hi - lo + 1));

      if( p == k )
         return &a[p];

      if( k < p )
         hi = p - 1;
      else
         lo = p + 1;
   }

   return 0;
}

// --- TEST ---
#include "rand.h"
#include <algorithm>
#include <iostream>

int * sortselect( Array & a, size_t k )
{
   if( a.empty() || k >= a.size() )
      return 0;

   std::sort( a.begin(), a.end() );
   return &a[k];
}

bool equal( int * x, int * y )
{
   if( !x && !y )
      return true;

   if( !x || !y )
      return false;

   return *x == *y;
}

void test( Array const & a )
{
   for( size_t i = 0; i <= a.size(); ++i )
   {
      Array b = a;
      Array c = a;

      int * x = quickselect( b, i );
      int * y = sortselect( c, i );

      if( !equal( x, y ) )
      {
         std::cout << a << std::endl;
         std::cout << i << std::endl;

         if( !x )
            std::cout << "x=<null>" << std::endl;
         else
            std::cout << "x=" << *x << std::endl;

         if( !y )
            std::cout << "y=<null>" << std::endl;
         else
            std::cout << "y=" << *y << std::endl;

         abort();
      }
   }
}

Array rand_array( size_t sz )
{
   Array a( sz );

   for( size_t i = 0; i < sz; ++i )
      a[ i ] = rand_range( -sz, sz );

   return a;
}

void test( size_t sz )
{
   test( rand_array(sz) );
}

int main()
{
   test( 0 );

   for( size_t sz = 0; sz < 16; ++sz )
      for( size_t i = 0; i < 100000; ++i )
         test( sz );
}
