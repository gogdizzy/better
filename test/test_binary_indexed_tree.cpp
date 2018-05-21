//
// Created by 关鑫 on 2018/5/21.
//

#include <stdio.h>
#include <tree/binary_indexed_tree.h>

template < typename T >
using bit_1d1mrq = better::binary_indexed_tree_1d1mrq< T >;

template < typename T >
using bit_1drm1q = better::binary_indexed_tree_1drm1q< T >;

template < typename T >
using bit_1drmrq = better::binary_indexed_tree_1drmrq< T >;

template < typename T >
using bit_1dmin = better::binary_indexed_tree_1dmin< T >;

int main() {

    bit_1d1mrq< int > bit1( 64 );

    bit1.modify( 1, 10 );

    bit1.modify( 2, 11 );

    bit1.modify( 3, 15 );

    printf( "%d\n", bit1.query( 1, 3 ) );
    printf( "%d\n", bit1.query( 2, 3 ) );
    printf( "%d\n", bit1.query( 1, 2 ) );

    bit_1drm1q< int > bit2( 64 );

    bit2.modify( 1, 64, 100 );

    printf( "%d\n", bit2.query( 50 ) );

    bit_1drmrq< int > bit3( 64 );

    bit3.modify( 1, 10, 5 );

    printf( "%d\n", bit3.query( 1, 5 ) );

    bit_1dmin< int > bit4( 64, std::greater< int >() );

    bit4.modify( 1, 4 );
    bit4.modify( 2, 3 );
    bit4.modify( 3, 2 );

    printf( "%d\n", bit4.query( 2, 3 ) );

    return 0;
}
