#include "merge_sort.h"
#include "rand.h"

#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <map>

static bool is_sorted( List const * x )
{
   if( !x )
      return true;

   while( x->next )
   {
      if( x->data > x->next->data )
         return false;

      x = x->next;
   }

   return true;
}

static List * rand_list( size_t sz, int l, int u )
{
   List * head = 0;

   while( sz-- > 0 )
   {
      List * x = new List( rand_range(l, u) );
      x->next = head;
      head = x;
   }

   return head;
}

typedef std::map<int, int> Map;

Map map( List * x )
{
   Map ret;

   while( x )
   {
      ret[ x->data ]++;
      x = x->next;
   }

   return ret;
}

static void test( size_t sz )
{
   List * x = rand_list( sz, -100, 100 );
   Map a = map( x );

   merge_sort( x );

   if( !is_sorted(x) || a != map(x) )
      abort();

   destroy( x );
}

int main()
{
   srand( time(0) );

   for( size_t sz=0; sz<20; ++sz )
      for( size_t i=0; i<100000; ++i )
         test( sz );
}
