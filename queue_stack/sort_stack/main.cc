#include <time.h>
#include <stdlib.h>
#include <limits.h>

#include <stack>
#include <iostream>

typedef std::stack< int > Stack;

std::ostream & operator<<( std::ostream & stream, Stack const & s )
{
   Stack copy       = s;
   char const * sep = "";

   stream << '[' << copy.size() << "](";

   while( !copy.empty() )
   {
      stream << sep << copy.top();
      copy.pop();
      sep = " ";
   }

   return stream << ')';
}

void sort( Stack & s )
{
   Stack tmp;

   while( !s.empty() )
   {
      int top = s.top();

      s.pop();

      while( !tmp.empty() && top > tmp.top() )
      {
         s.push( tmp.top() );
         tmp.pop();
      }

      tmp.push( top );
   }

   s = tmp;
}

void init( Stack & s, size_t sz )
{
   size_t max = sz * 2 + 1;

   while( sz-- )
   {
      s.push( rand() % max );
   }
}

bool sorted( Stack const & s )
{
   int prev = INT_MIN;

   Stack copy = s;

   while( !copy.empty() )
   {
      if( copy.top() < prev )
         return false;

      prev = copy.top();
      copy.pop();
   }

   return true;
}

void test( size_t sz )
{
   Stack s;

   init( s, sz );

   sort( s );

   if( !sorted(s) )
   {
      std::cout << s << std::endl;
      abort();
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz=0; sz<=10; ++sz )
   {
      for( size_t i=0; i<100000; ++i )
         test( sz );
   }
}
