#include "array.h"

void swap( int & a, int & b )
{
   int t = a;
   a     = b;
   b     = t;
}

void reverse( int a[], int lo, int hi )
{
   for( ; lo < hi; ++lo, --hi )
      swap( a[lo], a[hi] );
}

bool next_permutation( int a[], size_t len )
{
   if( len < 2 )
      return false;

   for( size_t i = len - 1; i > 0; --i )
   {
      if( a[i - 1] >= a[i] )
         continue;

      for( size_t j = len - 1; ; --j )
      {
         if( a[i - 1] >= a[j] )
            continue;

         swap( a[i - 1], a[j] );
         reverse( a, i, len - 1 );
         return true;
      }
   }

   reverse( a, 0, len - 1 );
   return false;
}

// --- TEST ---
#include "rand.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>

Array randArray( size_t sz )
{
   Array a( sz );

   for( size_t i = 0; i < sz; ++ i )
      a[ i ] = rand_range( 0, sz * 2 );

   std::sort( a.begin(), a.end() );
   return a;
}

void test( size_t sz )
{
   Array a = randArray( sz );
   Array b = a;

   for( ;; )
   {
      bool x = next_permutation( a.data(), a.size() );
      bool y = std::next_permutation( b.begin(), b.end() );

      if( x != y )
      {
         abort();
      }

      if( !x )
         break;
   }
}

int main()
{
   srand( time(0) );

   test( 0 );
   test( 1 );

   for( size_t sz = 2; sz < 9; ++sz )
      for( size_t i = 0; i < 10000; ++i )
         test( sz );
}
