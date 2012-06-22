#include "inorder.h"
#include <stack>

Array inorder( Tree const * tree )
{
   Array ret;

   std::stack< Tree const * > s;
   Tree const * current = tree;

   while( !s.empty() || current != 0 )
   {
      if( current != 0 )
      {
         s.push( current );
         current = current->left;
      }
      else
      {
         current = s.top();
         s.pop();

         ret.push_back( current->data );

         current = current->right;
      }
   }

   return ret;
}
