#ifndef ALGO_TREE_H_INCLUDED
#define ALGO_TREE_H_INCLUDED

#include <cstddef>

struct Tree
{
   int    data;
   Tree * left;
   Tree * right;

   explicit Tree( int d ):
      data( d ), left( 0 ), right( 0 )
   { }

   ~Tree()
   {
      delete left;
      delete right;
   }
};

void print( Tree const * root );
bool fill_rand( Tree * root, int minval, int maxval );
bool fill_rand_uniq( Tree * root, int minval, int maxval );
bool fill_rand_bst( Tree * root, int minval, int maxval );

// don't touch pointers in callback
void for_each_skel( void ( *cb )( Tree * x ), size_t maxsz, size_t minsz = 0 );

#endif // ALGO_TREE_H_INCLUDED
