#include "tree.h"
#include <algorithm>

Tree const * lower_bound( Tree const * p, int x )
{
   Tree const * ret = 0;

   while( p )
   {
      if( p->data == x )
         return p;

      if( p->data > x )
      {
         p = p->left;
      }
      else
      {
         ret = p;
         p = p->right;
      }
   }

   return ret;
}

Tree const * upper_bound( Tree const * p, int x )
{
   Tree const * ret = 0;

   while( p )
   {
      if( p->data > x )
      {
         ret = p;
         p = p->left;
      }
      else
      {
         p = p->right;
      }
   }

   return ret;
}

Tree const * findClosestElement( Tree const * root, int x )
{
   Tree const * l = lower_bound( root, x );
   Tree const * u = upper_bound( root, x );

   if( l && u )
      return std::abs(l->data - x) <= std::abs(u->data - x) ? l : u; // prefer smaller element

   return l ? l : u;
}

// -- TEST --
#include <ctime>
#include <cstdlib>
#include <iostream>

void findClosestElementBruteforce( Tree const * p, int x, Tree const *& candidate )
{
   if( !p )
      return;

   findClosestElementBruteforce( p->left, x, candidate );

   if( std::abs(p->data - x) < std::abs(candidate->data -x) )
      candidate = p;

   findClosestElementBruteforce( p->right, x, candidate );
}

Tree const * leftmost( Tree const * p )
{
   if( !p )
      return 0;

   while( p->left )
      p = p->left;

   return p;
}

Tree const * findClosestElementBruteforce( Tree const * root, int x )
{
   if( !root )
      return 0;

   Tree const * candidate = leftmost( root ); // prefer smaller element
   findClosestElementBruteforce( root, x, candidate );

   return candidate;
}

void test( Tree const * root, int x )
{
   Tree const * a = findClosestElement( root, x );
   Tree const * b = findClosestElementBruteforce( root, x );

   if( a != b )
   {
      std::cout << "x=" << x << " a=";

      if( a )
         std::cout << a->data;
      else
         std::cout << "(nil)";

      std::cout << " b=";

      if( b )
         std::cout << b->data;
      else
         std::cout << "(nil)";

      std::cout << '\n';

      print( root );

      abort();
   }
}

void test( Tree * root )
{
   if( !root )
   {
      test( root, 0 );
      return;
   }

   int const min = -10;
   int const max = 10;

   fill_rand_bst( root, min, max );

   for( int i = min - 5; i <= max + 5; ++i )
      test( root, i );
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 13 );
}
