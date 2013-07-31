#include "array.h"

static int bsearch( int a[], int len, int x )
{
   if( len <= 0 )
      return -1;

   int lo = 0;
   int hi = len - 1;

   while( lo <= hi )
   {
      int m = lo + (hi - lo) / 2;

      if( a[m] == x )
         return m;

      if( a[lo] <= a[m] )
      {
         if( x < a[lo] || x > a[m] )
            lo = m + 1;
         else
            hi = m - 1;
      }
      else
      {
         if( x < a[m] || x > a[hi] )
            hi = m - 1;
         else
            lo = m + 1;
      }
   }

   return -1;
}

// --- TEST ---
#include <cstdlib>
#include <iostream>
#include <algorithm>

static int lsearch( int a[], int len, int x )
{
   for( int i = 0; i < len; ++i )
      if( a[i] == x )
         return i;

   return -1;
}

static void init( Array & a, size_t sz )
{
   a.resize( sz );

   for( size_t i = 0; i < sz; ++i )
      a[i] = i * 2;
}

static void test( Array & a, int k )
{
   int x = bsearch( a.data(), a.size(), k );
   int y = lsearch( a.data(), a.size(), k );

   if( x != y )
   {
      std::cout << "k=" << k << " x=" << x << " y=" << y << std::endl;
      std::cout << a << std::endl;
      abort();
   }
}

static void test_empty()
{
   Array a;
   test( a, 1 );
}

static void test_single()
{
   Array a( 1, 1 );

   for( int i = 0; i < 2; ++i )
      test( a, i );
}

static void test_multi( int sz )
{
   Array a;

   init( a, sz );

   for( int i = 0; i <= sz; ++i )
   {
      std::rotate( a.begin(), a.begin() + 1, a.end() );

      for( int k = -1; k <= sz * 2; ++k )
         test( a, k );
   }
}

int main()
{
   test_empty();
   test_single();

   for( int sz = 2; sz < 20; ++sz )
      test_multi( sz );
}
