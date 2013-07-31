#include <algorithm>

struct Nut { int size; };
struct Bolt { int size; };

static int compare( Nut const & n, Bolt const & b )
{
   return n.size - b.size;
}

static int compare( Bolt const & b, Nut const & n )
{
   return b.size - n.size;
}

template< typename A, typename B >
static int partition( A * a, int l, int r, B const & b )
{
   int p = l;
   int q = r;

   // invariant:
   //  (1) a[k] < b  : k < p
   //  (2) a[k] > b  : k > q
   //  (3) a[k] == b : p <= k < i;
   //  (4) a[k] ?    : i <= k <= q
   for( int i = l; i <= q; )
   {
      int c = compare( a[i], b );

      if( c < 0 )
         std::swap( a[p++], a[i++] );
      else if( c == 0 )
         ++i;
      else
         std::swap( a[q--], a[i] );
   }

   return p;
}

static void qsort( Nut * nuts, Bolt * bolts, int l, int r )
{
   if( l >= r )
      return;

   int m  = l + (r - l) / 2;
   int bp = partition( bolts, l, r, nuts[m] );
   partition( nuts, l, r, bolts[bp] );

   qsort( nuts, bolts, l, bp - 1 );
   qsort( nuts, bolts, bp + 1, r );
}

static void qsort( Nut * nuts, Bolt * bolts, int size )
{
   qsort( nuts, bolts, 0, size - 1 );
}

// -- TEST --
#include <time.h>
#include <vector>
#include <iostream>

template< typename T >
static bool is_sorted( T const * a, int size )
{
   for( int i = 1; i < size; ++i )
      if( a[i-1].size > a[i].size )
         return false;

   return true;
}

template< typename T >
static std::ostream & print( std::ostream & stream, T const * a, int size )
{
   char const * sep = "";

   stream << '[' << size << "](";

   for( int i = 0; i < size; ++i )
   {
      stream << sep << a[i].size;
      sep = " ";
   }

   return stream << ')';
}

static void test( Nut * nuts, Bolt * bolts, int size )
{
   std::vector< Nut > nuts_input( nuts, nuts + size );
   std::vector< Bolt > bolts_input( bolts, bolts + size );

   qsort( nuts, bolts, size );

   if( !is_sorted( nuts, size ) || !is_sorted( bolts, size ) )
   {
      std::cout << "Input:\n";
      print( std::cout << "N: ", nuts_input.data(), size ) << '\n';
      print( std::cout << "B: ", bolts_input.data(), size ) << '\n';

      std::cout << "Output:\n";
      print( std::cout << "N: ", nuts, size ) << '\n';
      print( std::cout << "B: ", bolts, size ) << std::endl;

      abort();
   }
}

static void test( int size, int tries )
{
   std::vector< Nut > nuts( size );
   std::vector< Bolt > bolts( size );

   for( int i = 0; i < size; ++i )
   {
      nuts[i].size = i;
      bolts[i].size = i;
   }

   // test sorted
   test( nuts.data(), bolts.data(), size );

   // test reversed
   std::reverse( nuts.begin(), nuts.end() );
   std::reverse( bolts.begin(), bolts.end() );
   test( nuts.data(), bolts.data(), size );

   for( int i = 0; i < tries; ++i )
   {
      std::random_shuffle( nuts.begin(), nuts.end() );
      std::random_shuffle( bolts.begin(), bolts.end() );

      test( nuts.data(), bolts.data(), size );
   }
}

int main()
{
   srand( time(0) );

   test( 0, 1 );
   test( 1, 1 );

   for( int size = 2; size < 10; ++size )
      test( size, 100000 );
}
