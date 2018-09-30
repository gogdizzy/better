//
// Created by 关鑫 on 2018/9/4.
//

#include <cstdint>
#include <atomic>
#include <memory>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <boost/heap/fibonacci_heap.hpp>

namespace st = std::chrono;

struct Heap1 {
    std::priority_queue< int > Q, D;

    void push( int x ) { Q.push( x ); }

    void erase( int x ) { D.push( x ); }

    int top() {
        while( !D.empty() && Q.top() == D.top() ) Q.pop(), D.pop();
        return Q.empty() ? 0 : Q.top();
    }
};

struct Heap2 {
    typedef boost::heap::fibonacci_heap< int > _HEAP;
    _HEAP H;
    std::unordered_map< int, _HEAP::handle_type > M;

    void push( int x ) { M.insert( std::make_pair( x, H.push( x ) ) ); }

    void erase( int x ) { auto it = M.find( x ); H.erase( it->second ); M.erase( it ); }

    int top() {
        return H.top();
    }

    void pop() {
        H.pop();
    }
};

struct Heap3 {
    typedef std::set< int > _HEAP;
    _HEAP H;

    void push( int x ) { H.insert( x ); }

    void erase( int x ) { H.erase( x ); }

    int top() {
        return *H.cbegin();
    }

    void pop() {
        H.erase( H.begin() );
    }
};



int64_t POW10[19] =
        {
                1,
                10,
                100,
                1000,
                10000,
                100000,
                1000000,
                10000000,
                100000000,
                1000000000,
                10000000000,
                100000000000,
                1000000000000,
                10000000000000,
                100000000000000,
                1000000000000000,
                10000000000000000,
                100000000000000000,
                1000000000000000000
        };

template < typename T >
struct XX {
    typedef T int8_t;
    T x;
};

namespace NewGridMapConfig
{
constexpr size_t BLOCK_WIDTH = 128;
constexpr size_t BLOCK_HEIGHT = 32;
}

template <typename CellType, int USE_BIT = 0>
class NewGridMap
{
    using Dummy = typename std::enable_if< USE_BIT < 8 >::type;
    static constexpr int MASK[3] = { USE_BIT * 1, USE_BIT * 2, USE_BIT * 3 };
public:
    NewGridMap() {
        printf( "haha\n" );
    }
};

template <typename CellType>
class NewGridMap<CellType, 0> {
public:
    NewGridMap() {
        printf( "haha2\n" );
    }
};



int main() {

    constexpr size_t N = 100000000;

    std::atomic_long asum = 0;
    int64_t sum = 0;

    auto beg = st::high_resolution_clock::now();

//    for( size_t i = 0; i < N; ++i ) {
//        asum += i;
//    }
    Heap1 h;
    for( int i = 0; i < 400000; ++i ) h.push( i );
    for( int i = 0; i < 400000; ++i ) h.erase( i );

    // for( int i = 0; i < 10000000; ++i );
    auto end = st::high_resolution_clock::now();

    printf( "%lld\n", st::duration_cast< st::microseconds >(end - beg).count() );

    printf( "%lld\n", POW10[17] );
    printf( "%zd\n", sizeof( XX<float> ) );

    NewGridMap<int> g1;
    NewGridMap<int, 7> g2;
    NewGridMap<int, 0> g3;



//    std::map< int32_t, int32_t, std::less<int32_t>, MyAllocator< std::pair< const int32_t, int32_t > > > m1;
//    for( int i = 0; i < 100; ++i ) {
//        m1[i] = i + 10;
//    }



    return 0;
}

