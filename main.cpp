#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

int main(){
    pparse_init();
    
    pparse_object("$<4,2,3>{9999}");
    
    pparse_exit();
}