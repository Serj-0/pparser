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
    
//    pparse_object("$<long,int,float>{9999,85,0.055}");
//    meme = static_cast<fug*>(last_unprs_obj->object_data);
//    
//    cout << meme->a << endl << meme->b << endl << meme->c << endl;
    
    box a;
    pparse_object_to("$<float,float,float,float>{6.2,73.9,2.4,0.007}", box, a);
    
    cout << a.x << endl << a.y << endl << a.w << endl << a.h << endl;
    cout << a.x + a.y;
    
    pparse_exit();
}