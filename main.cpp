#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

int main(){
    pparse_init();
    
    pparse_object("w<423>{9999}");
    cout << uncase("rr<78?3>bbbbe32t", '<', '>');
    
    pparse_exit();
}