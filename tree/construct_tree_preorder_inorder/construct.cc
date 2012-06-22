#include "construct.h"
#include <map>

typedef std::map< int, size_t > Index;

static Tree * construct( int const * preorder, int left, int right, Index const & index )
{
   if( left > right )
      return 0;

   Tree * ret = new Tree( preorder[0] );

   size_t p = index.find( ret->data )->second;

   ret->left = construct( preorder + 1, left, p - 1, index );
   ret->right = construct( preorder + 1 + p - left, p + 1, right, index );

   return ret;
}

Tree * construct( Array const & preorder, Array const & inorder )
{
   if( preorder.empty() )
      return 0;

   // build index
   Index index;

   for( size_t i=0; i<inorder.size(); ++i )
      index[ inorder[i] ] = i;

   return construct( &preorder[0], 0, preorder.size() - 1, index );
}

