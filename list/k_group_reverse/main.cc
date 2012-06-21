#include "list.h"
#include <cstdlib>

List * remove_next( List * x )
{
   if( !x || !x->next )
      return 0;

   List * ret = x->next;
   x->next = ret->next;
   ret->next = 0;

   return ret;
}

void insert_next( List * prev, List * x )
{
   if( !prev )
      return;

   List * next = prev->next;
   prev->next = x;
   x->next = next;
}

List * reverse_first( List * x, size_t k, List ** last )
{
   if( k <= 1 || !x )
   {
      *last = 0;
      return x;
   }

   // dummy -> 1 -> 2 -> 3 -> 4 -> ...
   // dummy -> 2 -> 1 -> 3 -> 4 -> ...
   // dummy -> 3 -> 2 -> 1 -> 4 -> ...

   List dummy( 0, x );

   while( x->next && --k )
   {
      List * p = remove_next( x );
      insert_next( &dummy, p );
   }

   *last = k > 0 ? 0 : x;
   return dummy.next;
}

List * reverse( List * x, size_t k )
{
   List * p;

   x = reverse_first( x, k, &p );

   while( p )
   {
      List * t;
      p->next = reverse_first( p->next, k, &t );
      p = t;
   }

   return x;
}

// -- TEST --

#include <stdlib.h>
#include <vector>
#include <algorithm>

typedef std::vector< int > Array;

List * make_list( size_t sz )
{
   List * x = NULL;

   for( int i = sz; i > 0; --i )
   {
      x = push_front( x, i );
   }

   return x;
}

Array make_array( size_t sz )
{
   Array x( sz );

   for( size_t i=0; i<sz; ++i )
      x[i] = i+1;

   return x;
}

void assert( List * x, Array const & y )
{
   size_t i = 0;

   while( x && i < y.size() )
   {
      if( x->data != y[i] )
         abort();

      x = x->next;
      ++i;
   }

   if( x || i < y.size() )
      abort();
}

void reverse( Array & x, size_t k )
{
   if( k <= 1 )
      return;

   for( size_t i=0; i<x.size(); i+=k )
   {
      size_t j = std::min( k, x.size() - i );

      std::reverse( x.begin() + i, x.begin() + i + j );
   }
}

void test( size_t sz )
{
   List * x = make_list( sz );
   Array y = make_array( sz );

   assert( x, y );

   for( size_t k=0; k<sz+2; ++k )
   {
      x = reverse( x, k );
      reverse( y, k );

      assert( x, y );
   }

   destroy( x );
}

int main()
{
   for( size_t sz=0; sz < 1000; ++sz )
      test( sz );
}
