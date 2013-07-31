#include "array.h"

struct List
{
   int data;
   List * next;
   List * rand;

   List( int d ):
      data( d ), next( 0 ), rand( 0 )
   { }
};

List * clone( List * head )
{
   if( !head )
      return 0;

   List * p = head;
   while( p )
   {
      List * next = p->next;
      p->next = new List( p->data );
      p->next->next = next;
      p = next;
   }

   // populate rand
   p = head;
   while( p )
   {
      p->next->rand = p->rand->next;
      p = p->next->next;
   }

   // split
   List base( 0 );
   List * q = &base;
   p = head;

   while( p )
   {
      List * next = p->next;
      p->next = p->next->next;
      next->next = 0;
      q->next = next;
      q = q->next;
      p = p->next;
   }

   return base.next;
}

// -- TEST --
#include <ctime>
#include <cstdlib>
#include <iostream>

Array pattern( size_t sz )
{
   Array v( sz );

   for( size_t i = 0; i < sz; ++i )
      v[ i ] = rand() % sz;

   return v;
}

List * make( Array const & p )
{
   if( p.empty() )
      return 0;

   std::vector<List *> v( p.size() );

   for( size_t i = 0; i < p.size(); ++i )
      v[ i ] = new List( i );

   for( size_t i = 1; i < p.size(); ++i )
      v[ i - 1 ]->next = v[ i ];

   for( size_t i = 0; i < p.size(); ++i )
      v[ i ]->rand = v[ p[ i ] ];

   return v[ 0 ];
}

void destroy( List * x )
{
   while( x )
   {
      List * next = x->next;
      delete x;
      x = next;
   }
}

bool is_equal( List * a, List * b )
{
   while( a && b )
   {
      if( a->data != b->data )
         return false;

      if( a->rand->data != b->rand->data )
         return false;

      a = a->next;
      b = b->next;
   }

   return !a && !b;
}

void test( size_t sz )
{
   Array p = pattern( sz );

   List * a = make( p );
   List * b = clone( a );
   List * c = make( p );

   if( !is_equal(a, b) || !is_equal(a, c) )
   {
      std::cout << p << std::endl;
      abort();
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz = 0; sz < 10; ++sz )
      for( size_t i = 0; i < 100000; ++i )
         test( sz );
}
