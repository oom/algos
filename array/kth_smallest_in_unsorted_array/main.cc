#include <algorithm>

int partition( int a[], int l, int r, int p )
{
   int s = l;

   std::swap( a[p], a[r] );
   for( int i = l; i < r; ++i )
      if( a[i] < a[r] )
         std::swap( a[i], a[s++] );

   std::swap( a[s], a[p] );
   return s;
}

int kth_smallest( int a[], int l, int r, int k )
{
   while( l <= r )
   {
      int p = l + (r - l) / 2;
      p = partition( a, l, r, p );
      int d = p - l;


      if( k == d )
         return p;

      if( k > d )
      {
         l = p + 1;
         k = k - d;
      }
      else
      {
         r = p - 1;
         k = d - k;
      }
   }

   return -1;
}

int kth_smallest( int a[], int len, int k )
{
   if( len >= k )
      return -1;

   return kth_smallest( a, 0, len - 1, k );
}

// -- TEST --
#include "array.h"
#include "rand.h"
#include <map>
#include <iostream>

int kth_smallest_test( int a[], int len, int k )
{
   if( len >= k )
      return -1;

   typedef std::multimap< int, int > Map;
   Map m;

   for( int i = 0; i < len; ++i )
      m.insert( std::make_pair( a[i], i ) );

   Map::iterator i = m.begin();
   std::advance( i, k );

   return i->second;
}

Array randArray( size_t sz )
{
   Array ret( sz );

   for( size_t i = 0; i < sz; ++i )
      ret[ i ] = rand_range( -sz, sz );

   return ret;
}

void test( Array a, size_t k )
{
   Array b = a;

   int x = kth_smallest( a.data(), a.size(), k );
   int y = kth_smallest_test( b.data(), b.size(), k );

   bool good = ( x == y || ( x > 0 && y > 0 && a[x] == b[y] ) );

   if( !good )
   {
      std::cout << a << " k=" << k << " x=" << x << " y=" << y << std::endl;
      abort();
   }
}

void test( size_t sz )
{
   Array a = randArray( sz );

   for( size_t i = 0; i <= sz; ++i )
      test( a, i );
}

int main()
{
   srand( time(0) );

   test( 0 );
   test( 1 );

   for( size_t sz = 2; sz < 10; ++sz )
      for( size_t i = 0; i < 100000; ++i )
         test( sz );
}
