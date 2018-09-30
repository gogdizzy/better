//
// Created by 关鑫 on 2018/9/18.
//

#include <cstdio>
#include <type_traits>

enum class EA {
    A,
    B
};

enum class EB : int8_t {
    A = -1,
    B
};

int main() {

    printf( "EA size %d is_enum %d is_integral %d is_signed %d\n",
            sizeof( EA ),
            std::is_enum_v< EA >,
            std::is_integral_v< EA >,
            std::is_signed_v< EA > );
    printf( "EB size %d is_enum %d is_integral %d is_signed %d\n",
            sizeof( EB ),
            std::is_enum_v< EB >,
            std::is_integral_v< EB >,
            std::is_signed_v< EB > );

    return 0;
}


