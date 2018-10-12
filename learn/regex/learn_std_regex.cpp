//
// Created by 关鑫 on 2018/10/12.
//

#include <iostream>
#include <cstdio>
#include <regex>

void testBasic() {
    std::regex re1(".*(a|xayy)", std::regex::basic );
    std::smatch m;
    std::regex_search("zzxayyzz", m, re1, 0);
    std::cout << " ECMA (depth first search) match: " << m[0] << '\n';
}

void testExtended() {
    std::regex re2( ".*(a|xayy)", std::regex::extended );
}

int main() {

    testBasic();
    testExtended();

    return 0;
}