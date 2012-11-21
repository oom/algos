#include "list.h"
#include "array.h"
#include "rand.h"

#include <algorithm>
#include <iostream>

static void push( List * where, int x )
{
   List * n = new List( x, where->next );
   where->next = n;
}

static List * insert( List * head, int x )
{
   if( !head )
   {
      List * ret = new List( x );
      ret->next = ret;
      return ret;
   }

   List * cur = head;
   List * prev = 0;

   for( ;; )
   {
      if( cur->data < x )
      {
         prev = cur;
      }
      else if( prev )
      {
         push( prev, x );
         return head;
      }

      if( cur->next == head )
         break;

      cur = cur->next;
   }

   push( cur, x );
   return cur->data <= x ? head : cur->next;
}

// --- TEST ---
static void insert( Array & a, int x )
{
   a.push_back( x );
   std::sort( a.begin(), a.end() );
}

static bool equal( List * a, Array & b )
{
   if( !a )
      return b.empty();

   if( b.empty() )
      return false;

   List * p = a;
   size_t i = 0;

   do
   {
      if( p->data != b[ i ] )
         return false;

      p = p->next;
      ++i;
   } while( p != a && i < b.size() );

   return p == a && i == b.size();
}

static void test( size_t sz )
{
   List * a = 0;
   Array  b;

   while( sz-- > 0 )
   {
      int x = rand_range( 1, 10 );

      a = insert( a, x );
      insert( b, x );

      if( !equal( a, b ) )
      {
         std::cout << "insert " << x << std::endl;
         std::cout << a << std::endl;
         std::cout << b << std::endl;
         abort();
      }
   }

   destroy( a );
}

int main()
{
   srand( time(0) );

   for( int loop = 0; loop < 1000000; ++loop )
      test( 15 );
}
