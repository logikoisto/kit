#include "skiplist.h"
#include <iostream>
int main(int argc,char *argv[]){
    auto sl = KIT_NAMESPACE::SkipList();
    sl.set("b", 1);
    sl.set("a",2);
    sl.set("d", 1);
    std::cout << sl.get("a") << std::endl;
    return 0;
}