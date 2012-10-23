#include "list.h"
#include <cstdlib>
#include <iostream>

static List * remove_each_nth( List * head, size_t n )
{
   if( n == 0 )
      return head; // do nothing

   if( n == 1 )
   {
      destroy( head );
      return 0;
   }

   List * c = head;
   List * p = 0;
   size_t count = n;

   while( c )
   {
      if( count-- == 1 )
      {
         List * next = c->next;
         c->next = 0;
         destroy( c );
         p->next = next;
         c = next;
         count = n;
      }
      else
      {
         p = c;
         c = c->next;
      }
   }

   return head;
}

// ---- test ----

static List * create( size_t sz, size_t n )
{
   List base( 0 );
   List * p = &base;

   for( size_t i = 0; i < sz; ++i )
   {
      p->next = new List( 1 + (i % n) );
      p = p->next;
   }

   return base.next;
}

static bool verify( List * p, size_t n )
{
   for( size_t i = 0; p; ++i, p = p->next )
      if( p->data != 1 + (i % n) )
         return false;

   return true;
}

static void test( size_t sz, size_t n )
{
   List * p = remove_each_nth( create( sz, n ), n );

   if( !verify( p, n - 1 ) )
   {
      std::cout << "sz=" << sz << " n=" << n << '\n';
      std::cout << "-: " << create( sz, n ) << '\n';
      std::cout << "+: " << p << '\n';
      abort();
   }

   destroy( p );
}

int main()
{
   for( size_t sz = 0; sz < 100; ++sz )
      for( size_t n = 2; n <= sz; ++n )
         test( sz, n );
}
