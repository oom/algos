#include "list.h"
#include <ostream>

std::ostream & operator<<( std::ostream & os, List * x )
{
   char const * sep = "";

   os << '(';

   while( x )
   {
      os << sep << x->data;
      sep = ", ";
      x = x->next;
   }

   return os << ')';
}
