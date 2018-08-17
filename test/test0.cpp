//
// Created by 关鑫 on 2018/5/29.
//

#include <stdio.h>

#define MAXN 100000
#define MAXN1 100001

inline int lowbit( int x ) { return x & -x; }

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

int a[MAXN+1];

int main() {
    int n, m, op, x, y, k;
    binary_indexed_tree_1dkth< int > bit( MAXN + MAXN1 );
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; ++i ) {
        scanf( "%d", a + i );
        bit.modify( a[i] + MAXN1, 1 );
    }
    while( m-- ) {
        scanf( "%d", &op );
        if( op == 1 ) {
            scanf( "%d%d", &x, &y );
            bit.modify( a[x] + MAXN1, -1 );
            a[x] = y;
            bit.modify( y + MAXN1, 1 );
        }
        else {
            scanf( "%d", &k );
            printf( "%lld\n", ( bit.query( n + 1 - k * 2 ) - MAXN1 ) * ( long long ) ( bit.query( n + 2 - k * 2 ) - MAXN1 ) );
        }
    }
    return 0;
}
