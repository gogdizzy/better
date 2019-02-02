//
// Created by 关鑫 on 2018-12-04.
//

#include <stdio.h>
#include <string.h>
#include <queue>

#include "benchmark.h"

#define MAP_SIDE 100
#define MAP_OBS 5

int originMap[MAP_SIDE * MAP_SIDE];
int bubbledMap1[MAP_SIDE * MAP_SIDE];
int bubbledMap2[MAP_SIDE * MAP_SIDE];

void randMap() {
    memset( originMap, 0, sizeof( originMap ) );
    for( int i = 0; i < MAP_OBS; ++i ) {
        int x = rand() % MAP_SIDE;
        int y = rand() % MAP_SIDE;
        originMap[y * MAP_SIDE + x] = 5;
    }
}

void bubbleAlgo1() {
    memcpy( bubbledMap1, originMap, sizeof( bubbledMap1 ) );

    struct PointKey {
        int dist;
        int32_t x;
        int32_t y;

        PointKey() {}

        PointKey( int d, int32_t x, int32_t y ) : dist( d ), x( x ), y( y ) {}
    };
    struct PointKeyCmp {
        bool operator()( const PointKey &a, const PointKey &b ) const { return a.dist > b.dist; }
    };
    std::priority_queue< PointKey, std::vector< PointKey >, PointKeyCmp > distq;

    for( auto y = 0; y < MAP_SIDE; y++ ) {
        for( auto x = 0; x < MAP_SIDE; x++ ) {
            auto &cell = bubbledMap1[y * MAP_SIDE + x];
            if( cell > 0 ) {
                distq.push( PointKey( cell, x, y ) );
            }
        }
    }

    while( distq.size() > 0 ) {
        auto point = distq.top();
        distq.pop();
        auto dist = bubbledMap1[point.y * MAP_SIDE + point.x];
        if( dist != point.dist ) continue;

        if( dist > 1 ) {
            for( auto x = point.x - 1; x <= point.x + 1; x++ ) {
                for( auto y = point.y - 1; y <= point.y + 1; y++ ) {
                    if( ( x != point.x || y != point.y ) && ( 0 <= x && x < MAP_SIDE ) &&
                        ( 0 <= y && y < MAP_SIDE ) ) {
                        auto &cell = bubbledMap1[y * MAP_SIDE + x];
                        auto newDist = dist - 1;
                        if( newDist > cell ) {
                            cell = newDist;
                            distq.push( PointKey( newDist, x, y ) );
                        }
                    }
                }
            }
        }
    }
}

void bubbleAlgo2() {
    memcpy( bubbledMap2, originMap, sizeof( bubbledMap2 ) );

#define ASSIGN( x, y, v ) do { \
    if( ( 0 <= (x) && (x) < MAP_SIDE ) && ( 0 <= (y) && (y) < MAP_SIDE ) ) { \
        auto& __v = bubbledMap2[(y) * MAP_SIDE + (x)]; \
        if( v > __v ) __v = v; \
    } \
} while( 0 )

    for( auto y = 0; y < MAP_SIDE; y++ ) {
        for( auto x = 0; x < MAP_SIDE; x++ ) {
            auto &cell = bubbledMap2[y * MAP_SIDE + x];
            auto newDist = cell - 1;
            if( newDist > 0 ) {
                ASSIGN( x + 1, y, newDist );
                ASSIGN( x - 1, y + 1, newDist );
                ASSIGN( x, y + 1, newDist );
                ASSIGN( x + 1, y + 1, newDist );
            }
        }
    }

    for( auto y = MAP_SIDE - 1; y >= 0; --y ) {
        for( auto x = MAP_SIDE - 1; x >= 0; --x ) {
            auto &cell = bubbledMap2[y * MAP_SIDE + x];
            auto newDist = cell - 1;
            if( newDist > 0 ) {
                ASSIGN( x - 1, y, newDist );
                ASSIGN( x + 1, y - 1, newDist );
                ASSIGN( x, y - 1, newDist );
                ASSIGN( x - 1, y - 1, newDist );
            }
        }
    }
}

void verify() {
    assert( memcmp( bubbledMap1, bubbledMap2, sizeof( bubbledMap1 ) ) == 0 );
}

int main() {

    int N = 100;

    benchmark bm;

    randMap();

    bm.head( "", { "time" } );

    bm.content( "bubbleAlgo1", { [=]() { for( int i = 0; i < N; ++i ) bubbleAlgo1(); } } );
    bm.content( "bubbleAlgo2", { [=]() { for( int i = 0; i < N; ++i ) bubbleAlgo2(); } } );

    verify();

    return 0;
}