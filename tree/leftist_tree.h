// gogdizzy@qq.com
// 左偏树

#pragma once

#include <functional>
#include <utility>

namespace better {

template < typename T >
class leftist_tree {

public:
    leftist_tree( std::function< int( const T & ) > dist,
                  std::function< bool( const T &, const T & ) > cmp = std::less< T >() )
            : root( nullptr ), dist( dist ), cmp( cmp ) {}

    leftist_tree( T &&singleNode, std::function< int( const T & ) > dist,
                  std::function< bool( T, T ) > cmp = std::less< T >() )
            : root( &singleNode ), dist( dist ), cmp( cmp ) {}

    virtual ~leftist_tree() {

    }

    T *top() {
        return root;
    }

    T *pop() {

    }

    leftist_tree &add( T &&new_node ) {

        return *this;
    }

    static inline int h( T *node ) {
        return node == nullptr ? 0 : node->height;
    }

    static T *merge( T *a, T *b ) {
        if( a == nullptr ) return b;
        if( b == nullptr ) return a;
        if( cmp( *a, *b ) ) std::swap( a, b );
        a->rc = merge( a->rc, b );
        if( h( *a->lc ) < h( *a->rc ) ) std::swap( a->lc, a->rc );
        a->height = h( a->rc ) + 1;
    }

private:
    T *root;
    std::function< int( const T & ) > dist;
    std::function< bool( const T &, const T & ) > cmp;
};

leftist_tree operator+( leftist_tree &&a, leftist_tree &&b ) {

}

}
