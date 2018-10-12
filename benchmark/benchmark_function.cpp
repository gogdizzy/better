//
// Created by 关鑫 on 2018/9/30.
//
// See https://stackoverflow.com/questions/14677997/stdfunction-vs-template

#include <functional>
#include <string>

#include "benchmark.h"

template <typename F>
float calc1(F &&f) { return -1.0f * f(3.3f) + 666.0f; }

float calc2(const std::function<float(float)> &f) { return -1.0f * f(3.3f) + 666.0f; }

void testTemplate( int N ) {
    float rv = 0;
    auto f = [](float arg){ return arg * 0.5f; };
    for( int i = 0; i < N; ++i ) {
        rv += calc1( f );
    }
}

void testFunction( int N ) {
    float rv = 0;
    auto f = [](float arg){ return arg * 0.5f; };
    for( int i = 0; i < N; ++i ) {
        rv += calc2( f );
    }
}

int main() {
    int N = 1000000;

    benchmark bm( 20, 20 );
    bm.head( "", { "testTemplate", "testFunction" } );
    bm.content( "time", { [=]() { testTemplate( N ); }, [=]() { testFunction( N ); } } );

    return 0;
}
