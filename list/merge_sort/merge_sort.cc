#include "merge_sort.h"

// doesn't work if list size <= 1
static List * find_middle( List * x )
{
   if( !x )
      return 0;

   List * slow = x;
   List * fast = x->next;

   while( fast && fast->next )
   {
      fast = fast->next->next;
      slow = slow->next;
   }

   return slow;
}

static List * merge( List * x, List * y )
{
   List ret( 0 );
   List * p = &ret;

   while( x && y )
   {
      if( x->data <= y->data )
      {
         p->next = x;
         x = x->next;
      }
      else
      {
         p->next = y;
         y = y->next;
      }

      p = p->next;
   }

   if( x )
      p->next = x;

   if( y )
      p->next = y;

   return ret.next;
}

void merge_sort( List *& x )
{
   if( !x || !x->next )
      return;

   List * m = find_middle( x );

   List * y = m->next;
   m->next = 0;

   merge_sort( x );
   merge_sort( y );

   x = merge( x, y );
}
