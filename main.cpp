#include <iostream>

#include "DelimiterStringIterator.h"

int main() {
    std::string s = "aa,bbbbb,c,ddd";

    for (DelimiterStringIterator<','> ii(s); ii != DelimiterStringIterator<','>(); ++ii) {
        std::cout << (*ii) << std::endl;
    }

    return 0;
}
