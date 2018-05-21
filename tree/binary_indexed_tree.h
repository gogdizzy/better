// gogdizzy@qq.com
// 树状数组
// 使用须知：位置0是作为boundary的，所以查询和更新最小位置是1
// 命名规则：binary_indexed_tree_[x]d[y]m[z]q，d表示维度，m表示修改，q表示查询，1表示点，r表示范围
//         例如，binary_indexed_tree_1d1mrq表示一维，点修改，范围查询的树状数组

#pragma once

#include <functional>

#include <util/bitop.h>

namespace better {

using bitop::lowbit;

template < typename T >
class binary_indexed_tree_1d1mrq {

public:
    binary_indexed_tree_1d1mrq( int maxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >() ) {
        this->maxlen = maxlen;
        bit_a = new T[maxlen + 1];
        this->add = add;
        this->sub = sub;
    }

    virtual ~binary_indexed_tree_1d1mrq() {
        if( bit_a != nullptr ) delete[] bit_a;
    }

    // 修改点x的值，加v
    inline void modify( int x, T v ) {
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            bit_a[x] = add( bit_a[x], v );
        }
    }

    // 查询a[1..x]的和
    inline T query( int x ) {
        T s = T();
        for( x = x > maxlen ? maxlen : x; x > 0; x -= lowbit( x ) ) {
            s = add( s, bit_a[x] );
        }
        return s;
    }

    // 查询a[x1..x2]的和
    inline T query( int x1, int x2 ) {
        return sub( query( x2 ), query( x1 - 1 ) );
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // bit_a就是在a的基础上做树状数组
    int maxlen;
    T *bit_a;
    std::function< T( T, T ) > add;
    std::function< T( T, T ) > sub;
};


template < typename T >
class binary_indexed_tree_1drm1q {

public:
    binary_indexed_tree_1drm1q( int maxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >(),
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->maxlen = maxlen;
        bit_b = new T[maxlen + 1];
        this->add = add;
        this->sub = sub;
        this->neg = neg;
    }

    virtual ~binary_indexed_tree_1drm1q() {
        if( bit_b != nullptr ) delete[] bit_b;
    }

    // 修改a[1..x]的值，加v
    inline void modify( int x, T v ) {
        for( x = x > maxlen ? maxlen : x; x > 0; x -= lowbit( x ) ) {
            bit_b[x] = add( bit_b[x], v );
        }
    }

    // 修改a[x1..x2]的值，加v
    inline void modify( int x1, int x2, T v ) {
        modify( x2, v );
        modify( x1 - 1, neg( v ) );
    }

    // 查询点x的值
    inline T query( int x ) {
        T s = T();
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            s = add( s, bit_b[x] );
        }
        return s;
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // b[i]表示a[1..i]这个区间修改的值，则统计一个点被修改的值，只需要向上累计father值(即所有包含当前点的区间)
    // bit_b就是在b的基础上做树状数组
    int maxlen;
    T *bit_b;
    std::function< T( T, T ) > add;
    std::function< T( T, T ) > sub;
    std::function< T( T ) > neg;
};


template < typename T >
class binary_indexed_tree_1drmrq {

public:
    binary_indexed_tree_1drmrq( int maxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >(),
                                std::function< T( T ) > neg = std::negate< T >(),
                                std::function< T( T, int ) > mul = std::multiplies< T >() ) {
        this->maxlen = maxlen;
        bit_b = new binary_indexed_tree_1drm1q< T >( maxlen, add, sub, neg );
        bit_c = new binary_indexed_tree_1d1mrq< T >( maxlen, add, sub );
        this->add = add;
        this->sub = sub;
        this->neg = neg;
        this->mul = mul;
    }

    virtual ~binary_indexed_tree_1drmrq() {
        if( bit_b != nullptr ) delete bit_b;
        if( bit_c != nullptr ) delete bit_c;
    }

    inline void modify( int x, T v ) {
        bit_b->modify( x, v );
        bit_c->modify( x, mul( v, x ) );
    }

    inline void modify( int x1, int x2, T v ) {
        modify( x2, v );
        modify( x1 - 1, neg( v ) );
    }

    inline T query( int x ) {
        return add( mul( bit_b->query( x ), x ), bit_c->query( x - 1 ) );
    }

    inline T query( int x1, int x2 ) {
        return sub( query( x2 ), query( x1 - 1 ) );
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // b[i]表示a[1..i]这个区间修改的值，则统计一个点被修改的值，只需要向上累计father值(即所有包含当前点的区间)
    // c[i]表示a[1..i]这个区间累加的总和，即c[i] = b[i] * i
    // bit_b就是在b的基础上做树状数组
    // bit_c就是在c的基础上做树状数组

    int maxlen;
    binary_indexed_tree_1drm1q< T > *bit_b;
    binary_indexed_tree_1d1mrq< T > *bit_c;
    std::function< T( T, T ) > add;
    std::function< T( T, T ) > sub;
    std::function< T( T ) > neg;
    std::function< T( T, int ) > mul;
};


template < typename T >
class binary_indexed_tree_1dmin {

public:
    binary_indexed_tree_1dmin( int maxlen,
                               std::function< bool( T, T ) > cmp = std::less< T >() ) {
        this->maxlen = maxlen;
        a = new T[maxlen + 1];
        m = new T[maxlen + 1];
        this->cmp = cmp;
    }

    virtual ~binary_indexed_tree_1dmin() {
        if( a != nullptr ) delete[] a;
        if( m != nullptr ) delete[] m;
    }

    void modify( int p, T v ) {
        if( cmp( v, a[p] ) ) {
            a[p] = v;
            // 更新所有父节点，如果更新到某处，无需更新，那么更高层的节点也无需更新
            for( int i = p; i <= maxlen; i += lowbit( i ) ) {
                if( cmp( v, m[i] ) ) m[i] = v;
                else break;
            }
        } else {
            T oldv = a[p];
            a[p] = v;
            // 之前的最值不是a[p]，现在a[p]更大，更不可能是最值
            if( cmp( m[p], oldv ) ) return;

            int lbi;
            for( int i = p; i <= maxlen; i += lbi ) {
                // 如果m[i]的值没有更新，那么就不必检查父节点
                bool out = true;
                if( cmp( a[i], m[i] ) ) {
                    m[i] = a[i];
                    out = false;
                }
                lbi = lowbit( i );
                // 寻找i节点所有第一层子节点的最值
                for( int j = 1; j < lbi; j <<= 1 ) {
                    if( cmp( m[i - j], m[i] ) ) {
                        m[i] = m[i - j];
                        out = false;
                    }
                }
                if( out ) break;
            }
        }
    }

    T query( int l, int r ) {
        T ans = a[r--];
        int lbr;
        while( l <= r ) {
            lbr = lowbit( r );
            if( r - lbr >= l ) {
                if( cmp( m[r], ans ) ) ans = m[r];
                r -= lbr;
            } else {
                if( cmp( a[r], ans ) ) ans = a[r];
                --r;
            }
        }
        return ans;
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // m[i]表示a[1..i]这个区间最值

    int maxlen;
    T *a;
    T *m;
    std::function< bool( T, T ) > cmp;
};


}



