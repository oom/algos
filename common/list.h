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

inline void destroy( List * x )
{
   while( x )
   {
      List * next = x->next;
      delete x;
      x = next;
   }
}

std::ostream & operator<<( std::ostream & os, List * x );

#endif // ALGO_LIST_H_INCLUDED
