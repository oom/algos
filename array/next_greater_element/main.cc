#include "array.h"

#include <time.h>
#include <stdlib.h>

#include <stack>
#include <iostream>

Array bruteforce( Array const & a )
{
   Array result( a.size(), -1 );

   for( size_t i=0; i<a.size(); ++i )
      for( size_t j=i+1; j<a.size(); ++j )
         if( a[j] > a[i] )
         {
            result[i] = j;
            break;
         }

   return result;
}

Array smart( Array const & a )
{
   if( a.empty() )
      return Array();

   Array result( a.size(), -1 );

   std::stack< size_t > s;

   for( size_t i=0; i<a.size(); ++i )
   {
      while( !s.empty() && a[i] > a[s.top()] )
      {
         result[s.top()] = i;
         s.pop();
      }

      s.push( i );
   }

   return result;
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   for( size_t i=0; i<sz; ++i )
      a[ i ] = rand() % (sz * 2);
}

void test( size_t sz )
{
   Array a;

   init( a, sz );

   Array bf = bruteforce( a );
   Array sm = smart( a );

   if( bf != sm )
   {
      abort();
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz=0; sz<=10; ++sz )
      for( size_t i=0; i<100000; ++i )
         test( sz );
}
