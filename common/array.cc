#include "array.h"
#include <iostream>

std::ostream & operator<<( std::ostream & stream, Array const & a )
{
   char const * sep = "";

   stream << '[' << a.size() << "](";

   for( size_t i=0; i<a.size(); ++i )
   {
      stream << sep << a[i];
      sep = " ";
   }

   return stream << ')';
}
