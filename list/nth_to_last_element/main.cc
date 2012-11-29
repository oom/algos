#include "list.h"
#include <cstdlib>
#include <iostream>

static List * nth_to_last( List * head, size_t n )
{
   List * a = head;
   List * b = head;

   for( size_t i = 0; i < n && b; ++i )
      b = b->next;

   if( !b )
      return 0;

   while( b->next )
   {
      a = a->next;
      b = b->next;
   }

   return a;
}

// -- TEST --
static List * nth_from_start( List * head, size_t n )
{
   List * p = head;

   while( p && n-- > 0 )
      p = p->next;

   return p;
}

static List * reverse( List * x )
{
   List * ret = 0;

   while( x )
   {
      List * next = x->next;
      x->next = ret;
      ret = x;
      x = next;
   }

   return ret;
}

static List * nth_to_last_naive( List * head, size_t n )
{
   List * rev = reverse( head );
   List * ret = nth_from_start( rev, n );
   reverse( rev );

   return ret;
}

static List * create( size_t sz )
{
   List * ret = 0;

   for( size_t i = 0; i < sz; ++i )
      ret = new List( i, ret );

   return ret;
}

static void complain( List * l, size_t sz, List * a, List * b, size_t i )
{
   std::cout << "i=" << i << " sz=" << sz << std::endl;
   std::cout << "l=" << l << std::endl;

   if( !a )
      std::cout << "a=NULL" << std::endl;
   else
      std::cout << "a=" << a->data << std::endl;

   if( !b )
      std::cout << "b=NULL" << std::endl;
   else
      std::cout << "b=" << b->data << std::endl;

   abort();
}

static void test( size_t sz )
{
   List * l = create( sz );

   for( size_t i = 0; i <= sz + 1; ++i )
   {
      List * a = nth_to_last( l, i );
      List * b = nth_to_last_naive( l, i );

      if( (!!a) ^ (!!b) )
         complain( l, sz, a, b, i );

      if( a && ( a->data != b->data || a->data != i ) )
         complain( l, sz, a, b, i );
   }

   destroy( l );
}

int main()
{
   for( size_t sz = 0; sz < 10; ++sz )
      test( sz );
}
