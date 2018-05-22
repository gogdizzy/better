// gogdizzy@qq.com
// 树状数组
// 使用须知：位置0是作为boundary的，所以查询和更新最小位置是1
// 命名规则：binary_indexed_tree_[x]d[y]m[z]q，d表示维度，m表示修改，q表示查询，1表示点，r表示范围
//         例如，binary_indexed_tree_1d1mrq表示一维，点修改，范围查询的树状数组
//         特例，binary_indexed_tree_1dmin表示一维，点修改，范围查询最值
//         特例，binary_indexed_tree_1dkth表示一维，点修改，查询第k小

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
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->maxlen = maxlen;
        bit_b = new T[maxlen + 1];
        this->add = add;
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
    std::function< T( T ) > neg;
};


template < typename T >
class binary_indexed_tree_1drmrq {

public:
    binary_indexed_tree_1drmrq( int maxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >(),
                                std::function< T( T, int ) > mul = std::multiplies< T >(),
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->maxlen = maxlen;
        bit_b = new binary_indexed_tree_1drm1q< T >( maxlen, add, neg );
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
        if( x <= 0 ) return;
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
    std::function< T( T, int ) > mul;
    std::function< T( T ) > neg;
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
        }
        else {
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
            }
            else {
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


// 目前只支持固定数据种类，修改数据个数的模式
// 用户需要自己先将数据离散化，找到每个数据对应的排位
// 本数据结构只能处理排位数量更新，数据最大位置不超过2^30
template< typename T = int >
class binary_indexed_tree_1dkth {

public:
    binary_indexed_tree_1dkth( int maxlen ) {
        this->maxlen = maxlen;
        this->total = 0;
        bit_a = new T[maxlen + 1];
    }

    virtual ~binary_indexed_tree_1dkth() {
        if( bit_a != nullptr ) delete[] bit_a;
    }

    void modify( int x, int v ) {
        total += v;
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            bit_a[x] += v;
        }
    }

    int query( int kth ) {
        if( kth <= 0 || kth > total ) return -1;
        int p = 0;
        for( int i = 30; i >= 0; --i ) {
            int len = ( 1 << i );
            if( p + len <= maxlen && bit_a[p + len] < kth ) {
                kth -= bit_a[p + len];
                p += len;
            }
        }
        return p + 1;
    }

private:
    // 基于1，所以注意数组边界
    // a[i]第i个数字出现次数
    // bit_a就是在a的基础上做树状数组
    // 寻找第k小，就是一个逐渐逼近的过程，因为bit_a[i]表示了自己控制范围内的数字个数，
    // 所以先找左边最接近kth的2^x，然后依次缩小步长，找x右边最大的能逼近kth的2的幂

    int maxlen;
    T total;
    T *bit_a;
};


template < typename T >
class binary_indexed_tree_2d1mrq {

public:
    binary_indexed_tree_2d1mrq( int xmaxlen, int ymaxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >() ) {
        this->xmaxlen = xmaxlen;
        this->ymaxlen = ymaxlen;
        data = new T[( xmaxlen + 1 ) * ( ymaxlen + 1 )];
        for( int i = 0; i < ( xmaxlen + 1 ) * ( ymaxlen + 1 ); ++i ) data[i] = T();
        bit_a = new T *[ymaxlen + 1];
        for( int i = 0; i <= ymaxlen; ++i ) bit_a[i] = data + i * ( xmaxlen + 1 );
        this->add = add;
        this->sub = sub;
    }

    virtual ~binary_indexed_tree_2d1mrq() {
        if( bit_a != nullptr ) delete[] bit_a;
        if( data != nullptr ) delete[] data;
    }

    inline void modify( int x, int y, T v ) {
        if( x <= 0 || y <= 0 ) return;
        for( int j = y; 0 < j && j <= ymaxlen; j += lowbit( j ) ) {
            for( int i = x; 0 < i && i <= xmaxlen; i += lowbit( i ) ) {
                bit_a[j][i] = add( bit_a[j][i], v );
            }
        }
    }

    inline T query( int x, int y ) {
        T s = T();
        for( int j = y > ymaxlen ? ymaxlen : y; j > 0; j -= lowbit( j ) ) {
            for( int i = x > xmaxlen ? xmaxlen : x; i > 0; i -= lowbit( i ) ) {
                s = add( s, bit_a[j][i] );
            }
        }
        return s;
    }

    inline T query( int x1, int y1, int x2, int y2 ) {
        return sub( add( query( x2, y2 ), query( x1 - 1, y1 - 1 ) ), add( query( x2, y1 - 1 ), query( x1 - 1, y2 ) ) );
    }

private:
    // 基于1，所以注意数组边界
    // a[i][j]表示原来数组的值
    // bit_a就是在a的基础上做的2维树状数组

    int xmaxlen;
    int ymaxlen;
    T **bit_a;
    T *data;
    std::function< T( T, T ) > add;
    std::function< T( T, T ) > sub;
};


template < typename T >
class binary_indexed_tree_2drm1q {

public:
    binary_indexed_tree_2drm1q( int xmaxlen, int ymaxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->xmaxlen = xmaxlen;
        this->ymaxlen = ymaxlen;
        data = new T[( xmaxlen + 1 ) * ( ymaxlen + 1 )];
        for( int i = 0; i < ( xmaxlen + 1 ) * ( ymaxlen + 1 ); ++i ) data[i] = T();
        bit_b = new T *[ymaxlen + 1];
        for( int i = 0; i <= ymaxlen; ++i ) bit_b[i] = data + i * ( xmaxlen + 1 );
        this->add = add;
        this->neg = neg;
    }

    virtual ~binary_indexed_tree_2drm1q() {
        if( bit_b != nullptr ) delete[] bit_b;
        if( data != nullptr ) delete[] data;
    }


    inline void modify( int x, int y, T v ) {
        if( x <= 0 || y <= 0 ) return;
        for( int j = y > ymaxlen ? ymaxlen : y; j > 0; j -= lowbit( j ) ) {
            for( int i = x > xmaxlen ? xmaxlen : x; i > 0; i -= lowbit( i ) ) {
                bit_b[j][i] = add( bit_b[j][i], v );
            }
        }
    }

    inline void modify( int x1, int y1, int x2, int y2, T v ) {
        modify( x2, y2, v );
        modify( x2, y1 - 1, neg( v ) );
        modify( x1 - 1, y2, neg( v ) );
        modify( x1 - 1, y1 - 1, v );
    }

    inline T query( int x, int y ) {
        T s = T();
        for( int j = y; 0 < j && j <= ymaxlen; j += lowbit( j ) ) {
            for( int i = x; 0 < i && i <= xmaxlen; i += lowbit( i ) ) {
                s = add( s, bit_b[j][i] );
            }
        }
        return s;
    }

private:
    // 基于1，所以注意数组边界
    // a[i][j]表示原来数组的值
    // b[i][j]表示a[1..i][1..j]这个区域每个点被累计了多少值
    // bit_b就是在b的基础上做的2维树状数组

    int xmaxlen;
    int ymaxlen;
    T **bit_b;
    T *data;
    std::function< T( T, T ) > add;
    std::function< T( T ) > neg;
};


template < typename T >
class binary_indexed_tree_2drmrq {

public:
    binary_indexed_tree_2drmrq( int xmaxlen, int ymaxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T, T ) > sub = std::minus< T >(),
                                std::function< T( T, int ) > mul = std::multiplies< T >(),
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->xmaxlen = xmaxlen;
        this->ymaxlen = ymaxlen;
        bit_b = new binary_indexed_tree_2d1mrq< T >( xmaxlen, ymaxlen, add, sub );
        bit_c = new binary_indexed_tree_2d1mrq< T >( xmaxlen, ymaxlen, add, sub );
        bit_d = new binary_indexed_tree_2d1mrq< T >( xmaxlen, ymaxlen, add, sub );
        bit_e = new binary_indexed_tree_2d1mrq< T >( xmaxlen, ymaxlen, add, sub );
        this->add = add;
        this->sub = sub;
        this->mul = mul;
        this->neg = neg;
    }

    virtual ~binary_indexed_tree_2drmrq() {
        if( bit_b != nullptr ) delete bit_b;
        if( bit_c != nullptr ) delete bit_c;
        if( bit_d != nullptr ) delete bit_d;
        if( bit_e != nullptr ) delete bit_e;
    }

    inline void modify( int x, int y, T v ) {
        if( x <= 0 || y <= 0 ) return;
        bit_b->modify( x, y, v ), bit_b->modify( 1, y, neg( v ) ), bit_b->modify( x, 1, neg( v ) ),
                bit_b->modify( 1, 1, v );
        bit_c->modify( x, y, neg( mul( v, x ) ) ), bit_c->modify( x, 1, mul( v, x ) );
        bit_d->modify( x, y, neg( mul( v, y ) ) ), bit_d->modify( 1, y, mul( v, y ) );
        bit_e->modify( x, y, mul( v, x * y ) );
    }

    inline void modify( int x1, int y1, int x2, int y2, T v ) {
        modify( x2, y2, v );
        modify( x2, y1 - 1, neg( v ) );
        modify( x1 - 1, y2, neg( v ) );
        modify( x1 - 1, y1 - 1, v );
    }

    inline T query( int x, int y ) {
        if( x <= 0 || y <= 0 ) return T();
        return add( add( mul( bit_b->query( x, y ), x * y ), mul( bit_c->query( x, y ), y ) ),
                    add( mul( bit_d->query( x, y ), x ), bit_e->query( x, y ) )
        );
    }

    inline T query( int x1, int y1, int x2, int y2 ) {
        return sub( add( query( x2, y2 ), query( x1 - 1, y1 - 1 ) ),
                    add( query( x2, y1 - 1 ), query( x1 - 1, y2 ) )
        );
    }

private:
    // 参考http://hi.baidu.com/strongoier/item/13f22104f6b4c50d6c904852
    // 我日，太妙了
    // 基于1，所以注意数组边界
    // 把修改简记为(x', y')，加的数为d，询问简记为(x, y)
    // bit_b 当x' > x, y' > y时，(x', y')对(x, y)的贡献值为x * y * d，因此用树状数组维护所有(x, y)的sigma{d}
    // bit_c 当x' <= x, y' > y时，(x', y')对(x, y)的贡献值为x' * y * d，因此用树状数组维护所有(x, y)的sigma{x' * d}
    // bit_d 当x' > x, y' <= y时，(x', y')对(x, y)的贡献值为x * y' * d，因此用树状数组维护所有(x, y)的sigma{y' * d}
    // bit_e 当x' <= x, y' <= y时，(x', y')对(x, y)的贡献值为x' * y' * d，因此用树状数组维护所有(x, y)的sigma{x' * y' * d}

    int xmaxlen;
    int ymaxlen;
    binary_indexed_tree_2d1mrq< T > *bit_b;
    binary_indexed_tree_2d1mrq< T > *bit_c;
    binary_indexed_tree_2d1mrq< T > *bit_d;
    binary_indexed_tree_2d1mrq< T > *bit_e;
    std::function< T( T, T ) > add;
    std::function< T( T, T ) > sub;
    std::function< T( T, int ) > mul;
    std::function< T( T ) > neg;
};


}



