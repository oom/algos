#include "preorder.h"
#include <stack>

Array preorder( Tree const * tree )
{
   Array ret;
   std::stack< Tree const * > s;
   Tree const * current = tree;

   while( !s.empty() || current != 0 )
   {
      if( current != 0 )
      {
         ret.push_back( current->data );

         if( current->right )
            s.push( current->right );

         current = current->left;
      }
      else
      {
         current = s.top();
         s.pop();
      }
   }

   return ret;
}
