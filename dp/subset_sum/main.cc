#include "array.h"

#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <numeric>

// the sum of positive elements
int psum( Array const & a )
{
   int sum = 0;

   for( size_t i = 0; i < a.size(); ++i )
      if( a[i] > 0 )
         sum += a[i];

   return sum;
}

// the sum of negative elements
int nsum( Array const & a )
{
   int sum = 0;

   for( size_t i = 0; i < a.size(); ++i )
      if( a[i] < 0 )
         sum += a[i];

   return sum;
}

Array subset( Array const & a, int sum )
{
   int p = psum( a );
   int n = nsum( a );

   if( a.empty() || sum > p || sum < n )
      return Array();

   // The idea is to populate a matrix M where M[i][j] indicates
   // if there exists a subset of a[0]..a[i] which sum equals j.
   // Since indices can't be negative, a[i][0] holds value for n, a[i][1] for n + 1, etc.
   std::vector< Array > m( a.size(), Array(p - n + 1, false) );

   m[0][ a[0] - n ] = true;

   for( size_t i = 1; i < a.size(); ++i )
      for( size_t j = 0; j < m[i].size(); ++j )
      {
         int s = n + j - a[i];

         m[i][j] =
            ( a[i] == n + j ) ||
            ( m[i - 1][j] )   ||
            ( s >= n && s <= p && m[i - 1][s - n] );
      }

   int x = a.size() - 1;
   int y = sum;

   if( !m[x][y - n] )
      return Array();

   Array ret;

   do
   {
      while( x > 0 && m[x - 1][y - n] )
         --x;

      ret.push_back( a[x] );
      y -= a[x];
      --x;
   } while( y != 0 );

   std::reverse( ret.begin(), ret.end() );
   return ret;
}

Array subset_bruteforce( Array const & a, int sum )
{
   if( a.empty() )
   {
      return Array();
   }

   size_t count = (1 << a.size());

   for( size_t i = 1; i < count; ++i )
   {
      int s = 0;

      for( size_t j = 0; j < a.size(); ++j )
         if( i & (1 << j) )
            s += a[j];

      if( s == sum )
      {
         Array ret;

         for( size_t j = 0; j < a.size(); ++j )
            if( i & (1 << j) )
               ret.push_back( a[j] );

         return ret;
      }
   }

   return Array();
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   int lo = -sz;
   int hi = sz * 2 + 1;

   for( size_t i = 0; i < sz; ++i )
      a[i] = lo + (rand() % hi);
}

void test( size_t sz )
{
   Array a;

   init( a, sz );

   int n = nsum( a );
   int p = psum( a );

   for( int i = n - 1; i <= p + 1; ++i )
   {
      Array bf = subset_bruteforce( a, i );
      Array sm = subset( a, i );

      if( bf.empty() != sm.empty() ||
            (!bf.empty() && std::accumulate( bf.begin(), bf.end(), 0 ) != i) ||
            (!sm.empty() && std::accumulate( sm.begin(), sm.end(), 0 ) != i) )
      {
         std::cout << a << "\n  sum=" << i << "\n  bf: " << bf << "\n  sm: " << sm << std::endl;
         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz = 0; sz < 7; ++sz )
      for( size_t i = 0; i < 10000; ++i )
         test( sz );
}
