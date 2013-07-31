#include <stack>

class Queue
{
public:
   void push( int x )
   {
      m_push.push( x );
   }

   void pop()
   {
      refill();
      m_pop.pop();
   }

   bool empty()
   {
      return m_push.empty() && m_pop.empty();
   }

   size_t size() const
   {
      return m_push.size() + m_pop.size();
   }

   int front()
   {
      refill();
      return m_pop.top();
   }

private:
   void refill()
   {
      if( m_pop.empty() )
         while( !m_push.empty() )
         {
            m_pop.push( m_push.top() );
            m_push.pop();
         }
   }

private:
   std::stack< int > m_push;
   std::stack< int > m_pop;
};

// -- TEST --
#include <ctime>
#include <cstdlib>

#include <queue>
#include <algorithm>

bool rand_action(size_t sz)
{
   static size_t const MaxSize = 100;

   if(sz == 0)
      return true;

   if(sz >= MaxSize)
      return false;

   return rand() % 2;
}

int main()
{
   srand(time(0));

   Queue a;
   std::queue<int> b;

   for(size_t i=0; i<10000000; ++i)
   {
      bool push = rand_action(b.size());

      if( push )
      {
         int x = rand() % 100;

         a.push( x );
         b.push( x );
      }
      else
      {
         a.pop();
         b.pop();
      }

      if( a.empty() != b.empty() || a.size() != b.size() || ( !a.empty() && a.front() != b.front() ) )
         abort();
   }
}
