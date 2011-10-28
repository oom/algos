#include <vector>
#include <iostream>
#include <algorithm>

typedef std::vector< int > Array;

std::ostream & operator<<( std::ostream & stream, Array const & a )
{
   const char * sep = "";

   stream << '(';

   for( size_t i=0; i<a.size(); ++i )
   {
      stream << sep << a[i];
      sep = " ";
   }

   return stream << ')';
}

void shift_right( Array & a, size_t i, size_t j )
{
   if( i >= j )
      return;

   int tmp = a[j];

   for( size_t k=j; k>i; --k )
      a[k] = a[k-1];

   a[i] = tmp;
}

void interleave( Array & a )
{
   for( size_t i=0; i+2<a.size(); i+=2 )
   {
      size_t mid = i + (a.size()-i) / 2;

      std::swap( a[i+1], a[mid] );
      shift_right( a, i+2, mid );
   }
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   size_t mid = sz / 2;

   for( size_t i=0; i<mid; ++i )
   {
      a[i]     = i * 2;
      a[mid+i] = 1 + i * 2;
   }
}

bool is_sorted( Array const & a )
{
   for( size_t i=1; i<a.size(); ++i )
      if( a[i-1] > a[i] )
         return false;

   return true;
}

void test( size_t sz )
{
   Array a;

   init( a, sz );
   interleave( a );

   if( !is_sorted( a ) )
      abort();
}

int main()
{
   for( size_t sz=0; sz<100; sz += 2 )
      test( sz );
}
