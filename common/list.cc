#include "list.h"
#include <ostream>

std::ostream & operator<<( std::ostream & os, List * x )
{
   os << '(';

   if( x )
   {
      List * p = x;
      char const * sep = "";

      do
      {
         os << sep << p->data;
         sep = " ";
         p = p->next;
      } while( p && p != x );
   }

   return os << ')';
}
