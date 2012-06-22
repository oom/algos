#include "tree.h"
#include <vector>
#include <cstdlib>

typedef std::vector< unsigned int > Cookies;

class Pool
{
public:
   Pool();
   ~Pool();

   Tree * acquire();
   void reset();

private:
   Pool( Pool const & );
   Pool & operator=( Pool const & );

private:
   std::vector< Tree > m_pool;
   size_t m_pos;
};

Pool::Pool():
   m_pool(16, Tree(0)), m_pos(0)
{ }

Pool::~Pool()
{
   for( size_t i=0; i<m_pool.size(); ++i )
      m_pool[i].left = m_pool[i].right = 0;
}

Tree * Pool::acquire()
{
   if( m_pos == m_pool.size() )
      m_pool.push_back( Tree(0) );

   m_pool[m_pos] = Tree(0);

   return &m_pool[m_pos++];
}

void Pool::reset()
{
   m_pos = 0;
}

static Pool pool;

struct ibitstream
{
public:
   explicit ibitstream( unsigned int value ):
      m_value( value )
   { }

   bool get()
   {
      bool ret = m_value & 1;
      m_value >>= 1;
      return ret;
   }

private:
   unsigned int m_value;
};

struct obitstream
{
public:
   obitstream():
      m_value( 0 ),
      m_pos( 0 )
   { }

   void put( bool bit )
   {
#if 1
      if( bit && m_pos >= 31 )
         abort();
#endif

      m_value |= ( (!!bit) << m_pos );
      ++m_pos;
   }

   unsigned int uint() const
   {
      return m_value;
   }

private:
   unsigned int m_value;
   unsigned int m_pos;
};

static void serialize( Tree const * x, obitstream & os )
{
   if( !x )
   {
      os.put(false);
   }
   else
   {
      os.put(true);
      serialize( x->left, os );
      serialize( x->right, os );
   }
}

static unsigned int serialize( Tree const * x )
{
   obitstream os;
   serialize( x, os );
   return os.uint();
}

static Tree * deserialize( ibitstream & is )
{
   if( !is.get() )
      return 0;

   Tree * x = pool.acquire();

   x->left = deserialize( is );
   x->right = deserialize( is );

   return x;
}

static Tree * deserialize( unsigned int skel )
{
   ibitstream is( skel );
   return deserialize( is );
}

static void copySubtree( obitstream & os, ibitstream & is )
{
   if( !is.get() )
   {
      os.put(false);
   }
   else
   {
      os.put(true);
      copySubtree( os, is );
      copySubtree( os, is );
   }
}

static void copySubtree( obitstream & os, unsigned int skel )
{
   ibitstream is( skel );
   copySubtree( os, is );
}

static void invoke( void ( *cb )( Tree * x ), unsigned int cookie )
{
   Tree * x = deserialize( cookie );
   cb( x );
   pool.reset();
}

void for_each_skel( void ( *cb )( Tree * x ), size_t maxsz, size_t minsz )
{
   maxsz = std::min<size_t>( maxsz, 16 );
   std::vector< Cookies > dp( maxsz + 1 );

   dp[ 0 ].push_back( 0 );

   if( minsz == 0 )
      invoke( cb, 0 );

   for( size_t i=1; i<=maxsz; ++i )
   {
      size_t cnt = 0;

      for( size_t lsz=0; lsz<i; ++lsz )
         cnt += dp[ lsz ].size() * dp[ i - lsz - 1 ].size();

      dp[ i ].reserve( cnt );

      for( size_t lsz=0; lsz<i; ++lsz )
      {
         Cookies & left  = dp[ lsz ];
         Cookies & right = dp[ i - lsz - 1 ];

         for( Cookies::const_iterator l = left.begin(); l != left.end(); ++l )
            for( Cookies::const_iterator r = right.begin(); r != right.end(); ++r )
            {
               obitstream os;

               os.put(true); // root
               copySubtree( os, *l );
               copySubtree( os, *r );

               dp[ i ].push_back( os.uint() );

               if( i >= minsz )
                  invoke( cb, os.uint() );
            }
      }
   }
}
