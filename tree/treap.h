//
// Created by 关鑫 on 2018/8/17.
//

#pragma once

#include <random>

namespace better {

/**
 * 二叉搜索树
 * 内部节点带一个额外的随机权重，按照堆的方法调整，从而实现随机平衡
 */

template < typename T >
class treap {
    typedef std::function< bool( const T &, const T & ) > cmp_func;
    typedef std::function< int() > rand_func;
public:
    struct node {
        T value;
        int weight;
        size_t size;
        node *lc;
        node *rc;
    };

    treap( const cmp_func &cmp = std::less< T >(), const rand_func &rand = rand_weight() )
            : root( nullptr ), cmp( cmp ), rand( rand ) {}

    void insert( const T &val ) {

    }

    void erase( const T &val ) {

    }

protected:
    static int rand_weight() {
        static std::random_device rd;
        static std::mt19937 gen( rd() );
        static std::uniform_int_distribution<> dis( 1, 6 );
        return dis();
    }

private:
    node *root;
    cmp_func cmp;
    rand_func rand;
};

}
