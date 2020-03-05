#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

int main(){
    pparse_init();
    
    parse_object("$<423>{9999}");
    
    pparse_exit();
}