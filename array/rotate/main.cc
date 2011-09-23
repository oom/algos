#include <stdlib.h>

#include <vector>
#include <iostream>
#include <algorithm>

typedef std::vector< int > Array;

std::ostream & operator<<( std::ostream & stream, Array const & a )
{
   char const * sep = "";

   stream << '[' << a.size() << "](";

   for( size_t i=0; i<a.size(); ++i )
   {
      stream << sep << a[i];
      sep = " ";
   }

   return stream << ')';
}

void reverse( int a[], size_t len )
{
   size_t m = len / 2;

   for( size_t i=0; i<m; ++i )
   {
      int tmp = a[i];
      a[i] = a[len-i-1];
      a[len-i-1] = tmp;
   }
}

void rotate_reverse( int a[], size_t len, int k )
{
   if( len == 0 )
      return;

   if( k < 0 || k >= len )
   {
      k %= len;

      if( k < 0 )
         k += len;
   }

   if( k == 0 )
      return;

   reverse( a, k );
   reverse( a+k, len-k );
   reverse( a, len );
}

void rotate_cycle( int a[], size_t len, int k )
{
   if( len == 0 )
      return;

   if( k < 0 || k >= len )
   {
      k %= len;

      if( k < 0 )
         k += len;
   }

   if( k == 0 )
      return;

   for( size_t c = 0, v = 0; c < len; ++v )
   {
      size_t t  = v;
      size_t tp = v + k;
      int tmp   = a[v];

      ++c;

      while( tp != v )
      {
         a[t] = a[tp];
         t    = tp;
         tp   = (tp + k) % len;
         ++c;
      }

      a[t] = tmp;
   }
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   for( size_t i=0; i<sz; ++i )
      a[ i ] = i;
}

void test( size_t sz )
{
   Array a;

   init( a, sz );

   Array b = a;
   Array c = a;

   for( size_t i=0; i<sz; ++i )
   {
      Array prev = a;

      rotate_reverse( &a[0], a.size(), i );
      rotate_reverse( &b[0], b.size(), i );
      std::rotate( c.begin(), c.begin() + i, c.end() );

      if( a != b || a != c )
      {
         std::cout << prev << " rotate " << i << ":\n" << a << '\n' << b << '\n' << c << std::endl;
         abort();
      }
   }
}

int main()
{
   for( size_t sz=0; sz<100; ++sz )
      test( sz );
}
