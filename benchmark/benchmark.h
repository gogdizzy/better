//
// Created by 关鑫 on 2018/10/11.
//

#pragma once

#include <cstdio>
#include <chrono>
#include <functional>

class benchmark {
    using fun = std::function< void() >;
public:
    benchmark( int catalog_width = 16, int item_width = 16 ) : catalog_width( catalog_width ), item_width( item_width ) {}

    void head( const char *catalog, std::initializer_list< const char * > heads ) {
        printf( "%*s", catalog_width, catalog );
        for( auto h : heads ) {
            printf( "%*s", item_width, h );
        }
        printf( "\n" );
    }

    void content( const char *catalog, std::initializer_list< const fun > funs ) {
        printf( "%*s", catalog_width, catalog );
        for( auto &f : funs ) {
            auto beg = std::chrono::high_resolution_clock::now();
            f();
            auto end = std::chrono::high_resolution_clock::now();
            printf( "%*lld", item_width, std::chrono::duration_cast< std::chrono::microseconds >(end - beg).count() );
        }
        printf( "\n" );
    }

private:
    int catalog_width;
    int item_width;
};
