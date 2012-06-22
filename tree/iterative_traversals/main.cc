#include "inorder.h"
#include "preorder.h"
#include "postorder.h"

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>

static void recursive_inorder( Tree const * root, Array & out )
{
   if( !root )
      return;

   recursive_inorder( root->left, out );
   out.push_back( root->data );
   recursive_inorder( root->right, out );
}

static Array recursive_inorder( Tree const * root )
{
   Array ret;
   recursive_inorder( root, ret );
   return ret;
}

static void recursive_preorder( Tree const * root, Array & out )
{
   if( !root )
      return;

   out.push_back( root->data );
   recursive_preorder( root->left, out );
   recursive_preorder( root->right, out );
}

static Array recursive_preorder( Tree const * root )
{
   Array ret;
   recursive_preorder( root, ret );
   return ret;
}

static void recursive_postorder( Tree const * root, Array & out )
{
   if( !root )
      return;

   recursive_postorder( root->left, out );
   recursive_postorder( root->right, out );
   out.push_back( root->data );
}

static Array recursive_postorder( Tree const * root )
{
   Array ret;
   recursive_postorder( root, ret );
   return ret;
}

static void test( Tree * root, Array (*iterative)(Tree const *), Array (*recursive)(Tree const *), char const * name )
{
   Array i = iterative( root );
   Array r = recursive( root );

   if( i != r )
   {
      print( root );
      puts( "---" );
      std::cout << name << " iterative: " << i << std::endl;
      std::cout << name << " recursive: " << r << std::endl;
      abort();
   }
}

static void test( Tree * root )
{
   fill_rand_uniq( root, -10, 10 );

   test( root, inorder, recursive_inorder, "inorder" );
   test( root, preorder, recursive_preorder, "preorder" );
   test( root, postorder, recursive_postorder, "postorder" );
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 16 );
}
