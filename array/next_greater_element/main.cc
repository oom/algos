#include <time.h>
#include <stdlib.h>

#include <stack>
#include <vector>
#include <iostream>

typedef std::vector<int> Array;

Array bruteforce( Array const & a )
{
   Array result( a.size(), -1 );

   for( size_t i=0; i<a.size(); ++i )
   {
      for( size_t j=i+1; j<a.size(); ++j )
      {
         if( a[j] > a[i] )
         {
            result[i] = j;
            break;
         }
      }
   }

   return result;
}

Array smart( Array const & a )
{
   if( a.empty() )
   {
      return Array();
   }

   Array result( a.size() );

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

   while( !s.empty() )
   {
      result[s.top()] = -1;
      s.pop();
   }

   return result;
}

void init( Array & a, size_t size )
{
   a.resize( size );

   for( size_t i=0; i<size; ++i )
   {
      a[ i ] = rand() % (size * 2);
   }
}

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

void test( size_t size )
{
   Array a;

   init( a, size );

   Array bf = bruteforce( a );
   Array sm = smart( a );

   if( bf != sm )
   {
      abort();
   }
}

void test()
{
   size_t const MaxSize = 10;
   size_t const Rounds  = 100000;

   for( size_t i=0; i<=MaxSize; ++i )
   {
      for( size_t r=0; r<Rounds; ++r )
      {
         test( i );
      }
   }
}

int main()
{
   srand( time(0) );

   test();
}
