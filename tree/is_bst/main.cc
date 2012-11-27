#include "tree.h"
#include <ctime>
#include <cstdlib>

bool isBstImpl( Tree * root, int * min, int * max )
{
   if( !root )
      return true;

   if( min && root->data <= *min )
      return false;

   if( max && root->data >= *max )
      return false;

   return
      isBstImpl( root->left, min, &root->data ) &&
      isBstImpl( root->right, &root->data, max );
}

bool isBst( Tree * root )
{
   return isBstImpl( root, NULL, NULL );
}

void test_bst( Tree * root )
{
   fill_rand_bst( root, -100, 100 );

   if( !isBst( root ) )
      abort();
}

int main()
{
   srand( time(0) );
   for_each_skel( &test_bst, 16 );
}
