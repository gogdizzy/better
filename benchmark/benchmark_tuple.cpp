//
// Created by 关鑫 on 2018/9/30.
//

#include <cstdint>
#include <tuple>

#include "benchmark.h"

inline void GetXY( const int index, int& x, int &y) {
    x = ( index >> 16 );
    y = (int16_t) ( index & 0xFFFF );
}

inline std::tuple< int32_t, int32_t > GetXY( const int32_t index ) {
    int32_t x = ( index >> 16 );
    int32_t y = (int16_t) ( index & 0xFFFF );
    return std::make_tuple( x, y );
}

//void benchmark( const std::function< void() > &func ) {
//    auto beg = st::high_resolution_clock::now();
//    func();
//    auto end = st::high_resolution_clock::now();
//    printf( "%20lld", st::duration_cast< st::microseconds >(end - beg).count() );
//}

void testReturnByRef( int N ) {
    int32_t x, y;
    for( int i = 0; i < N; ++i ) {
        GetXY( 10241024, x, y );
    }
}

void testReturnByTuple( int N ) {
    int32_t x, y;
    for( int i = 0; i < N; ++i ) {
        std::tie( x, y ) = GetXY( 10241024 );
    }
}

int main() {

    int N = 1000000;

    benchmark bm( 20, 20 );
    bm.head( "", { "testReturnByRef", "testReturnByTuple" } );
    bm.content( "time", { [=]() { testReturnByRef( N ); }, [=]() { testReturnByTuple( N ); } } );

    return 0;
}