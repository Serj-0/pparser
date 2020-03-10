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

    pparse_file("yy.ppff");
    
    pparse_exit();
}