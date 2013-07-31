#include "list.h"

static List * swap( List * head )
{
   List base( -1, head );
   List * p = &base;

   while( p->next && p->next->next )
   {
      List * a = p->next;
      List * b = a->next;

      // was: p -> a -> b -> c ....
      // now: p -> b -> a -> c ...

      a->next = b->next;
      b->next = a;
      p->next = b;

      p = a;
   }

   return base.next;
}

// ---- TEST ----
#include "array.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>

static List * create( size_t sz )
{
   List base( -1 );
   List * p = &base;

   for( size_t i = 0; i < sz; ++i )
   {
      p->next = new List(i);
      p = p->next;
   }

   return base.next;
}

static List * dumb_swap( List * x )
{
   Array dumb;

   while( x )
   {
      dumb.push_back( x->data );
      x = x->next;
   }

   for( size_t i = 0; i + 1 < dumb.size(); i += 2 )
      std::swap( dumb[i], dumb[i+1] );

   destroy( x );

   List base( -1 );
   x = &base;

   for( size_t i = 0; i < dumb.size(); ++i )
   {
      x->next = new List( dumb[i] );
      x = x->next;
   }

   return base.next;
}

static bool is_equal( List * a, List * b )
{
   while( a && b )
   {
      if( a->data != b->data )
         return false;

      a = a->next;
      b = b->next;
   }

   return !a && !b;
}

static void test( size_t sz )
{
   List * a = swap( create( sz ) );
   List * b = dumb_swap( create( sz ) );

   if( !is_equal( a, b ) )
   {
      std::cout << "sz=" << sz << std::endl;
      std::cout << "was: " << create( sz ) << std::endl;
      std::cout << "a:   " << a << std::endl;
      std::cout << "b:   " << b << std::endl;

      abort();
   }

   destroy( a );
   destroy( b );
}

int main()
{
   for( size_t sz = 0; sz < 100; ++sz )
      test( sz );
}
