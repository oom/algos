#ifndef ALGO_LIST_H_INCLUDED
#define ALGO_LIST_H_INCLUDED

#include <iosfwd>

struct List
{
   int data;
   List * next;

   explicit List( int d, List * n = 0 ):
      data( d ), next( n )
   { }
};

inline List * push_front( List * head, int data )
{
   return new List( data, head );
}

// works for circular lists as well
inline void destroy( List * a )
{
   if( !a )
      return;

   List * p = a;

   do
   {
      List * next = p->next;
      delete p;
      p = next;
   } while( p && p != a );
}

std::ostream & operator<<( std::ostream & os, List * x );

#endif // ALGO_LIST_H_INCLUDED
