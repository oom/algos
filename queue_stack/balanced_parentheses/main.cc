#include <stdlib.h>

#include <stack>
#include <string>
#include <iostream>

bool is_open(char c)
{
   return c == '(' || c == '{' || c == '[';
}

bool match(char open, char close)
{
   if( open == '(' )
      return close == ')';

   if( open == '{' )
      return close == '}';

   if( open == '[' )
      return close == ']';

   return false;
}

bool is_balanced(std::string const & s)
{
   std::stack<char> stack;

   for(size_t i=0; i<s.size(); ++i)
   {
      if( is_open(s[i]) )
      {
         stack.push( s[i] );
      }
      else
      {
         if( stack.empty() || !match( stack.top(), s[i] ) )
            return false;

         stack.pop();
      }
   }

   return stack.empty();
}

void test( std::string const & s, bool expected )
{
   bool actual = is_balanced(s);

   if( expected != actual )
   {
      std::cout << s << ": expected=" << expected << ", actual=" << actual << std::endl;
      abort();
   }
}

int main()
{
   test( "", true );
   test( "()", true );
   test( ")(", false );
   test( "{}", true );
   test( "[]", true );
   test( "[()]", true );

   test( "(", false );
   test( "(]", false );
   test( "[(])", false );
}
