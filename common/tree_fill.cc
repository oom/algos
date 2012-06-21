#include "tree.h"
#include "rand.h"

bool fill_rand( Tree * root, int minval, int maxval )
{
   if( !root )
      return true;

   if( minval > maxval )
      return false;

   root->data = rand_range( minval, maxval );

   return
      fill_rand( root->left, minval, maxval ) &&
      fill_rand( root->right, minval, maxval );
}

static size_t size( Tree const * x )
{
   if( !x )
      return 0;

   return 1 + size( x->left ) + size( x->right );
}

bool fill_rand_bst( Tree * root, int minval, int maxval )
{
   if( !root )
      return true;

   int left   = minval + size( root->left );
   int right  = maxval - size( root->right );

   if( left > right )
      return false;

   root->data = rand_range( left, right );

   return
      fill_rand_bst( root->left, minval, left - 1 ) &&
      fill_rand_bst( root->right, right + 1, maxval );
}