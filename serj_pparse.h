#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#define PPARSE_ERR_LOG "[PPARSE ERROR]: "
#include <string>

#include "serj_pparse_llist.h"
using namespace std;

namespace serj{

//prepare pparse for usage
void pparse_init(){
    init_unparsed_objects();
}

//exit pparse
void pparse_exit(){
    destroy_unparsed_objects();
}

//parse file data to usable object
void parse_object(string data){
    if(data[0] != '$'){
        cerr << PPARSE_ERR_LOG << " Invalid object initial character.\n";
        return;
    }
    int bsize = stoi(data.substr(2, data.length() - data.find_first_of(">", 2, data.length())));
    cout << bsize;
}

}

#endif /* SERJ_PPARSE_H */

