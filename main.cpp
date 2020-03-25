#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

struct fuck{
    long a;
    string str;
    char c;
};

int main(){
    pparse_init();

    pparse_file("yy.ppff");
    
    fuck ab = pparse_cast(fuck);
    cout << ab.a << endl;
    cout << ab.str << endl;
    cout << ab.c;
    
    pparse_exit();
}