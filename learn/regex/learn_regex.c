//
// Created by 关鑫 on 2018/10/11.
//

#include <stdio.h>
#include <regex.h>

void check( const regex_t *handle, int rv ) {
    char msg[256];
    if( rv != 0 ) {
        regerror( rv, handle, msg, sizeof( msg ) );
        printf( "Regex Compile Error: %s\n", msg );
    }
}

void testBasic() {
    regex_t handle;

    // BRE比较麻烦的就是元字符前面需要加\, 而因为cpp编译时会做转义，所以要用\\才行
    // regcomp的最后一个参数可以是以下几个值的组合
    // REG_EXTENDED 扩展正则ERE
    // REG_ICASE 忽略大小写
    // REG_NOSUB 不保留match位置，只返回是否匹配
    // REG_NEWLINE 对\n是否敏感，如果敏感，那么'^'，'$'这样的就可以在\n的位置匹配了，不过'.'，'[^...]'都不可以匹配\n
    // 可能还有一些扩展的选项，具体看文档介绍吧
    int rv = regcomp( &handle, "a\\{2\\}\\(b\\)c\\", REG_BASIC ); // 特意写了一个非法的正则式
    check( &handle, rv );

    regfree( &handle );
}

void testExtended() {
    regex_t handle;
    regmatch_t matches[32];
    char msg[256];
    int rv = regcomp( &handle, "a(b)*c", REG_EXTENDED );
    check( &handle, rv );

    // regexec的最后一个参数
    // REG_NOTBOL 指定字符串的开始并不是一行的开始
    // REG_NOTEOL 指定字符串的结束并不是一行的结束
    // 可能还有一些扩展的选项，具体看文档介绍吧
    rv = regexec( &handle, "adc", 0, NULL, REG_NOTBOL | REG_NOTEOL );
    check( &handle, rv );

    // regexec的返回值
    // 0 匹配
    // REG_NOMATCH 不匹配
    // REG_ESPACE 运行中内存超出
    rv = regexec( &handle, "abc", 32, matches, 0 );
    check( &handle, rv );
    printf( "subexpression count %zu\n", handle.re_nsub );
    printf( "" );

    regfree( &handle );
}

int main() {
    testBasic();
    testExtended();
    return 0;
}

