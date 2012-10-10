#include "tree.h"
#include <cstdlib>
#include <list>
#include <iostream>

Tree * lca( Tree * root, Tree * x, Tree * y )
{
   if( root == 0 || root == x || root == y )
      return root;

   Tree * left = lca( root->left, x, y );
   Tree * right = lca( root->right, x, y );

   if( left != 0 && right != 0 )
      return root;

   return left != 0 ? left : right;
}

typedef std::list< Tree * > Nodes;

bool get_path( Tree * root, Tree * x, Nodes & path )
{
   path.push_back( root );

   if( root == x )
      return true;

   if( root->left && get_path( root->left, x, path ) )
      return true;

   if( root->right && get_path( root->right, x, path ) )
      return true;

   path.pop_back();
   return false;
}

Nodes get_path( Tree * root, Tree * x )
{
   Nodes ret;

   if( root != 0 )
      get_path( root, x, ret );

   return ret;
}

Tree * bruteforce( Tree * root, Tree * x, Tree * y )
{
   Nodes xp = get_path( root, x );
   Nodes yp = get_path( root, y );

   Tree * last = 0;

   Nodes::const_iterator i = xp.begin();
   Nodes::const_iterator j = yp.begin();

   for( ; i != xp.end() && j != yp.end() && *i == *j; ++i, ++j )
      last = *i;

   return last;
}

void collect_nodes( Tree * root, Nodes & nodes )
{
   if( root == 0 )
      return;

   nodes.push_back( root );
   collect_nodes( root->left, nodes );
   collect_nodes( root->right, nodes );
}

void test_lca( Tree * root )
{
   Nodes nodes;

   fill_rand_bst( root, 10, 99 );
   collect_nodes( root, nodes );

   for( Nodes::const_iterator i = nodes.begin(); i != nodes.end(); ++i )
      for( Nodes::const_iterator j = nodes.begin(); j != nodes.end(); ++j )
      {
         Tree * a = lca( root, *i, *j );
         Tree * b = bruteforce( root, *i, *j );

         if( a != b )
         {
            print( root );
            std::cout << "---" << std::endl;
            std::cout << "lca(" << (*i)->data << ", " << (*j)->data << "): " << a->data << std::endl;
            std::cout << "bf(" << (*i)->data << ", " << (*j)->data << "):  " << b->data << std::endl;
            abort();
         }
      }
}

int main()
{
   srand( time(0) );
   for_each_skel( &test_lca, 16 );
}
