//
// Created by 关鑫 on 2018/9/15.
//

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <chrono>

#include <boost/heap/fibonacci_heap.hpp>

namespace st = std::chrono;

typedef int32_t UNIT;
typedef int8_t UNIT2;

static size_t PEAK;

template <typename _Tp>
class MyAllocator : public std::allocator< _Tp > {
public:
    typedef size_t            size_type;
    typedef ptrdiff_t         difference_type;
    typedef _Tp*              pointer;
    typedef const _Tp*        const_pointer;
    typedef _Tp&              reference;
    typedef const _Tp&        const_reference;
    typedef _Tp               value_type;

    template <class U1> struct rebind { typedef MyAllocator<U1> other; };

    MyAllocator() : total(0), peak(0) {}
    MyAllocator( const std::allocator<_Tp>& alloc ) : total(0), peak(0) {
    }
    ~MyAllocator() {
        PEAK += get_peak();
    }

    pointer allocate(size_type __n, std::allocator<void>::const_pointer = 0)
    {
        size_type cur = __n * sizeof(_Tp);
        total += cur;
        if( total > peak ) peak = total;
        // printf( "alloc %zd bytes, now total %zd bytes\n", cur, total );
        return std::allocator< _Tp >::allocate( __n );
    }

    void deallocate(pointer __p, size_type __n )
    {
        size_type cur = __n * sizeof(_Tp);
        total -= cur;
        // printf( "dealloc %zd bytes, now total %zd bytes\n", cur, total );
        return std::allocator< _Tp >::deallocate( __p, __n );
    }

    const size_type get_peak() { return peak; }

private:
    size_type total;
    size_type peak;
};



void benchmark( const std::function< void() > &func ) {
    PEAK = 0;
    auto beg = st::high_resolution_clock::now();
    func();
    auto end = st::high_resolution_clock::now();
    printf( "memory_peak:%10zd time:%10lld\n", PEAK, st::duration_cast< st::microseconds >(end - beg).count() );
}

void testVector( int N ) {
    std::vector< int, MyAllocator< int > > v1;
    for( int i = 0; i < N; ++i ) v1.push_back( i );
    for( int i = 0; i < N * 10; ++i ) auto x = v1[rand() % 100];
    for( int i = 0; i < N; ++i ) v1.pop_back();
}

void testMap( int N ) {
    std::map< UNIT, UNIT2, std::less<UNIT>, MyAllocator< std::pair< const UNIT, UNIT2 > > > m1;
    for( int i = 0; i < N; ++i ) m1.insert( std::make_pair( i, i ) );
    for( int i = 0; i < N * 10; ++i ) auto x = m1[rand() % 100];
    for( int i = 0; i < N; ++i ) m1.erase( i );
}

void testUnorderedmap( int N ) {
    std::unordered_map< UNIT, UNIT2, std::hash<UNIT>, std::equal_to<UNIT>, MyAllocator< std::pair< const UNIT, UNIT2 > > > m2;
    for( int i = 0; i < N; ++i ) m2.insert( std::make_pair( i, i ) );
    for( int i = 0; i < N * 10; ++i ) auto x = m2[rand() % 100];
    for( int i = 0; i < N; ++i ) m2.erase( i );
}

void testSet( int N ) {
    std::set< UNIT, std::less< UNIT >, MyAllocator< UNIT > > s1;
    for( int i = 0; i < N; ++i ) s1.insert( i );
    for( int i = 0; i < N * 10; ++i ) auto x = *s1.cbegin();
    for( int i = 0; i < N; ++i ) s1.erase( i );
}

void testPriorityQueue( int N ) {
    std::priority_queue< UNIT, std::vector< UNIT, MyAllocator< UNIT > > > q1;

    for( int i = 0; i < N; ++i ) q1.push( i );
    for( int i = 0; i < N * 10; ++i ) auto x = q1.top();
    for( int i = 0; i < N; ++i ) q1.pop();
}

void testFibonacci( int N ) {
    boost::heap::fibonacci_heap< UNIT, MyAllocator< UNIT > > h1;

    for( int i = 0; i < N; ++i ) h1.push( i );
    for( int i = 0; i < N * 10; ++i ) auto x = h1.top();
    for( int i = 0; i < N; ++i ) h1.pop();
}

template <typename T>
int sign(T v)
{
    if (v > 0)
        return 1;
    else if (v < 0)
        return -1;
    else
        return 0;
}

void TraverseLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, std::function<void (int32_t , int32_t , bool&)> handle8Connect, std::function<void (int32_t , int32_t , bool&)> handle4Connect)
{
    int32_t x = xs, y = ys;
    int32_t dx = abs(xe - xs);
    int32_t dy = abs(ye - ys);
    int32_t sx = sign(xe - xs);
    int32_t sy = sign(ye - ys);
    bool flag;
    if (dy > dx)
    {
        std::swap(dx, dy);
        flag = 1;
    }
    else
        flag = 0;

    int32_t nerror = 2 * dy - dx;

    bool stopTraverse = false;
    for (int32_t i = 0; i <= dx; i++)
    {
        handle8Connect(x, y, stopTraverse);
        if(stopTraverse)
            break;

        if (nerror >= 0)
        {
            if (flag)
                x = x + sx;
            else
                y = y + sy;
            nerror = nerror - 2 * dx;

            if (handle4Connect != nullptr)
            {
                handle4Connect(x, y, stopTraverse);
                if(stopTraverse)
                    break;
            }
        }
        if (flag)
            y = y + sy;
        else
            x = x + sx;
        nerror = nerror + 2 * dy;
    }
}

int main() {
    srand( time( nullptr ) );
    std::vector<int> arr{ 1, 10, 100, 1000, 10000, 100000, 1000000 };
    for( auto n : arr ) {
        printf( "========== TEST %d ELEMENTS ============\n", n );
        printf( "std::vector                 " ); benchmark( [=]() { testVector( n ); } );

        printf( "std::map                    " ); benchmark( [=]() { testMap( n ); } );
        printf( "std::unordered_map          " ); benchmark( [=]() { testUnorderedmap( n ); } );

        printf( "std::set                    " ); benchmark( [=]() { testSet( n ); } );
        printf( "std::priority_queue         " ); benchmark( [=]() { testPriorityQueue( n ); } );
        printf( "boost::heap::fibonacci_heap " ); benchmark( [=]() { testFibonacci( n ); } );
        printf( "\n" );
    }

//    printf( "handle size %zd\n", sizeof(typename boost::heap::fibonacci_heap< UNIT, MyAllocator< UNIT > >::handle_type) );

//    auto func8 = [](int32_t x, int32_t y, bool&) {
//        printf( "(%d,%d) 8\n", x, y );
//    };
//
//    auto func4 = [](int32_t x, int32_t y, bool&) {
//        printf( "(%d,%d) 4\n", x, y );
//    };
//
//    TraverseLine( 1, 1, 5, 8, func8, func4 );

}

