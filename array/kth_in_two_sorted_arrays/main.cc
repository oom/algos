#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include <vector>
#include <iostream>
#include <algorithm>

typedef std::vector< int > Array;

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

int dumb(Array const & a, Array const & b, size_t k)
{
   Array u(a);

   u.insert(u.end(), b.begin(), b.end());
   std::sort(u.begin(), u.end());

   if(k >= u.size())
      return INT_MIN;

   return u[k];
}

int better(Array const & a, Array const & b, size_t k)
{
   size_t i = 0;
   size_t j = 0;

   while(i < a.size() && j < b.size())
   {
      int val;

      if(a[i] < b[j])
         val = a[i++];
      else
        val = b[j++];

      if( k-- == 0 )
         return val;
   }

   for(; i < a.size(); ++i)
   {
      if( k-- == 0 )
         return a[i];
   }

   for(; j < b.size(); ++j)
   {
      if( k-- == 0 )
         return b[j];
   }

   return INT_MIN;
}

int best(Array const & a, Array const & b, size_t k)
{
   if(k >= a.size() + b.size())
      return INT_MIN;

   size_t count = k + 1;

   // Consider `count' smallest elements coming from the union of a and b.
   // l of them come from the first array, count -l come from the second.

   // We are trying to determine how many elements come from the first array.
   // This number is within the following range inclusive:
   size_t begin = std::max<int>(0, count - b.size());
   size_t end   = std::min(a.size(), count);

   // Use binary search to find how many elements come from the first array.
   while(begin < end)
   {
      int l = begin + (end - begin) / 2;

      // Consider the case when l elements come from the first array, count-l come from the second one.

      if( l < a.size() && count-l > 0 && a[l] < b[count-l-1] )
      {
         // If a[l] < b[count-l-1] we should take more elements from the first array.
         // In other words we should include a[l] into the k smallest elements.
         begin = l + 1;
      }
      else if( l > 0 && count-l < b.size() && a[l-1] > b[count-l] )
      {
         // If b[count-l] < a[l-1] we should take more elements from the second array.
         end = l - 1;
      }
      else
      {
         begin = l;
         break;
      }
   }

   if(begin == 0)
      return b[count-1];

   if(begin == count)
      return a[count-1];

   return std::max(a[begin-1], b[count-begin-1]);
}

void generate(Array & a, size_t sz)
{
   a.resize(sz);

   size_t mod = sz * 2 + 1;

   for(size_t i=0; i<sz; ++i)
      a[i] = rand() % mod;

   std::sort(a.begin(), a.end());
}

void test(size_t sz)
{
   Array a, b;

   generate(a, rand() % (sz+1) );
   generate(b, rand() % (sz+1) );

   for(size_t i=0; i<=sz*2+1; ++i)
   {
      int x = dumb(a, b, i);
      int y = better(a, b, i);
      int z = best(a, b, i);

      if( x != y || x != z )
      {
         std::cout << "A: " << a << "\nB: " << b << "\nk=" << i << " x=" << x << " y=" << y << " z=" << z << std::endl;
         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for(int i=0; i<10; ++i)
   {
      for(int j=0; j<1000000; ++j)
         test(i);
   }
}
