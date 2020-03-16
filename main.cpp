#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

struct fuck{
    int a;
    float b[3];
};

int main(){
    pparse_init();

    pparse_file("yy.ppff");
    
    cout << last_uncst_obj->object_string << endl
         << last_uncst_obj->object_label << endl;
    
    pparse_exit();
}