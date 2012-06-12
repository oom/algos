#include "array.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>

struct Range
{
   ssize_t start;
   ssize_t end;

   Range():
      start( 1 ), end( 0 )
   { }

   Range( ssize_t s, ssize_t e ):
      start( s ), end( e )
   { }

   ssize_t size() const { return end - start; }
};

void generate( Array & a, size_t size, int maxval )
{
   a.resize( size );

   for( size_t i=0; i<size; ++i )
   {
      a[ i ] = rand() % (maxval+1);
   }
}

ssize_t rfind_gt( Array const & a, size_t i )
{
   for( size_t j=a.size()-1; j>i; --j )
   {
      if( a[j] > a[i] )
         return j;
   }

   return i-1;
}

Range bruteforce( Array const & a, bool verbose = false )
{
   Range result;

   for( size_t i=0; i<a.size(); ++i )
   {
      Range x( i, rfind_gt( a, i ) );

      if( x.size() > result.size() )
      {
         if( verbose )
            std::cout << "BR: " << x.start << ' ' << x.end << std::endl;

         result = x;
      }
   }

   return result;
}

Range smart( Array const & a, bool verbose = false )
{
   if( a.size() < 2 )
   {
      return Range();
   }

   Array lmin( a.size() );
   Array rmax( a.size() );

   lmin[ 0 ] = a[ 0 ];
   for( size_t i = 1; i < a.size(); ++i )
   {
      lmin[ i ] = std::min( a[ i ], lmin[ i - 1 ] );
   }

   rmax[ a.size() - 1 ] = a[ a.size() - 1 ];
   for( ssize_t i = a.size() - 2; i >= 0; --i )
   {
      rmax[ i ] = std::max( a[ i ], rmax[ i + 1 ] );
   }

   if( verbose )
   {
      std::cout << "A: " << a << std::endl;
      std::cout << "L: " << lmin << std::endl;
      std::cout << "R: " << rmax << std::endl;
   }

   Range result;
   size_t i = 0;
   size_t j = 0;

   while( i < a.size() && j < a.size() )
   {
      if( verbose )
      {
         std::cout << i << ':' << j << ": " << lmin[i] << ' ' << rmax[j] << std::endl;
      }

      if( lmin[ i ] < rmax[ j ] )
      {
         Range x( i, j );

         if( verbose )
         {
            std::cout << x.size() << ':' << result.size() << std::endl;
         }

         if( x.size() > result.size() )
         {
            result = x;
         }

         ++j;
      }
      else
      {
         ++i;
      }
   }

   return result;
}

void test( size_t size )
{
   Array a;

   generate( a, size, 50 );

   Range b = bruteforce( a );
   Range s = smart( a );

   if( b.start != s.start || b.end != s.end )
   {
      b = bruteforce( a, true );
      s = smart( a, true );

      std::cout << '[' << b.start << ' ' << b.end << "]: " << a << '\n';
      std::cout << '[' << s.start << ' ' << s.end << "]: " << a << '\n';

      abort();
   }

}

int main()
{
   srand( time(0) );

   for( int i=0; i<100000; ++i )
      test( 5 );
}
