#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

struct box{
    float x, y;
    float w, h;
};

int main(){
    pparse_init();
    
    pparse_object("$<float,float,float,float>{6.2,73.9,2.4,0.0099}");
    box a = cast_pparsed_object(box);
    
    cout << a.x << endl << a.y << endl << a.w << endl << a.h << endl;
    cout << a.x + a.y;
    
    pparse_exit();
}