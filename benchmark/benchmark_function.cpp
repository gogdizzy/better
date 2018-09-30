//
// Created by 关鑫 on 2018/9/30.
//
// See https://stackoverflow.com/questions/14677997/stdfunction-vs-template

#include <stdio.h>
#include <functional>
#include <string>
#include <chrono>

namespace st = std::chrono;

template <typename F>
float calc1(F &&f) { return -1.0f * f(3.3f) + 666.0f; }

float calc2(const std::function<float(float)> &f) { return -1.0f * f(3.3f) + 666.0f; }

void benchmark( const std::function< void() > &func ) {
    auto beg = st::high_resolution_clock::now();
    func();
    auto end = st::high_resolution_clock::now();
    printf( "%20lld", st::duration_cast< st::microseconds >(end - beg).count() );
}

void testTemplate( int N ) {
    auto f = [](float arg){ return arg * 0.5f; };
    for( int i = 0; i < N; ++i ) {
        calc1( f );
    }
}

void testFunction( int N ) {
    auto f = [](float arg){ return arg * 0.5f; };
    for( int i = 0; i < N; ++i ) {
        calc2( f );
    }
}

int main() {
    int N = 1000000;

    printf( "                  testTemplate        testFunction\n" );
    printf( "time      " ); benchmark( [=]() { testTemplate( N ); } ); benchmark( [=]() { testFunction( N ); } ); printf( "\n" );

    return 0;
}
