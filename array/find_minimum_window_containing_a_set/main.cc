#include <cstddef>
#include <string>
#include <utility>

typedef std::pair< size_t, size_t > Interval; // [first, second)

Interval find_min_findow( std::string const & string, std::string const & set )
{
   Interval minwin( 0, 0 );
   size_t minlen = string.size() + 1;

   int in_set[256] = { 0 };
   size_t in_window[256] = { 0 };
   size_t found = 0;

   for( size_t i=0; i<set.size(); ++i )
      ++in_set[ set[i] ];

   size_t start = 0;
   size_t end = 0;

   for( size_t start = 0, end = 0; end < string.size(); ++end )
   {
      char e = string[end];

      if( in_set[e] == 0 )
         continue;

      ++in_window[e];

      if( in_window[e] <= in_set[e] )
         ++found;

      if( found == set.size() )
      {
         while( in_set[ string[start] ] == 0 ||
               in_set[ string[start] ] > in_window[ string[start] ] )
         {
            --in_window[ string[start] ];
            ++start;
         }

         size_t len = end - start + 1;

         if( minlen > len )
         {
            minlen = len;
            minwin = std::make_pair(start, end + 1);
         }
      }
   }

   return minwin;
}

int main()
{
}
