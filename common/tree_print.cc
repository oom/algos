#include "tree.h"
#include <queue>
#include <cstdio>

static int int_width( int x )
{
   if( x < 0 ) // TODO: INT_MIN?
      return 1 + int_width( -x );

   int w = 1;

   for( ; x >= 10; x /= 10, ++w ) { ; }

   return w;
}

static void print_space( int width )
{
   while( width-- > 0 )
      putchar( ' ' );
}

static void print_node( Tree const * x, int field_width )
{
   int data_width = int_width( x->data );
   int before = ( field_width - data_width ) / 2;
   int after  = field_width - data_width - before;

   print_space( before );
   printf( "%d", x->data );
   print_space( after );
}

static int max_int_width( Tree const * x )
{
   if( !x )
      return 0;

   return std::max(
         int_width( x->data ),
         std::max(
            max_int_width(x->left),
            max_int_width(x->right) ) );
}

static int depth( Tree const * x )
{
   if( !x )
      return 0;

   return 1 + std::max( depth(x->left), depth(x->right) );
}

static int leftmost_depth( Tree const * x )
{
   if( !x )
      return 0;

   return 1 + leftmost_depth( x->left );
}

static int pow2( int e )
{
   return 1 << e;
}

static int indent( int level, int depth, int space_width )
{
   return space_width * ( pow2(depth - level - 1) - 1 );
}

static int space_width( int level, int depth, int w )
{
   return w * ( pow2(depth - level) - 1 );
}

struct Info
{
   int          level;
   int          offset;
   Tree const * node;

   Info( int l, int o, Tree const * n ):
      level( l ), offset( o ), node( n )
   { }
};

void print( Tree const * root )
{
   if( !root )
      return;

   int w                 = max_int_width( root );
   int d                 = depth( root );
   int offset            = w * ( pow2( d - leftmost_depth(root) ) - 1 );
   int last_level        = -1;
   int last_offset       = -1;
   char const * line_sep = "";

   std::queue< Info > queue;

   queue.push( Info(0, 0, root) );

   while( !queue.empty() )
   {
      Info i = queue.front();
      queue.pop();

      int sw = space_width(i.level, d, w);

      if( last_level != i.level )
      {
         printf( "%s", line_sep );
         print_space( indent(i.level, d, w) + i.offset * (w + sw) - offset );

         last_level  = i.level;
         last_offset = i.offset;
         line_sep    = "\n";
      }
      else
      {
         int cnt = 2 * ( i.offset - last_offset - 1 ) + 1;
         print_space( cnt * sw );

         last_offset = i.offset;
      }

      print_node( i.node, w );

      if( i.node->left )
         queue.push( Info(i.level+1, i.offset*2, i.node->left) );

      if( i.node->right )
         queue.push( Info(i.level+1, i.offset*2+1, i.node->right) );
   }

   puts( "" );
}
