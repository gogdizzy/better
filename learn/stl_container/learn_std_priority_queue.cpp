//
// Created by 关鑫 on 2018/10/12.
//

#include <cstdio>
#include <queue>

void testBasic() {
    std::priority_queue< int > pq;
    pq.push( 1 );
    pq.push( 2 );
    pq.push( 3 );
    pq.push( 4 );
    pq.push( 5 );
    while( pq.size() > 0 ) {
        int x = pq.top();
        pq.pop();
        printf( "%d ", x );
    }
    printf( "\n" );
}

int main() {

    testBasic();

    return 0;
}