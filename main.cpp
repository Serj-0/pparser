#include <iostream>
#include "serj_pparse_llist.h"
#include "serj_pparse.h"
using namespace std;
using namespace serj;

struct int10{
    int arr[10];
};

int main(){
    pparse_init();

    pparse_object("$<int_3>{4_3}");
    int10 a = cast_pparsed_object(int10);
    
    for (int i = 0; i < 10; i++) {
        cout << a.arr[i] << endl;
    }

    
    pparse_exit();
}