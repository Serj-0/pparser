#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include "serj_pparse_llist.h"

namespace serj{

void pparse_init(){
    init_unparsed_objects();
}

void pparse_exit(){
    destroy_unparsed_objects();
}

void parse_object(string data){
    
}

}

#endif /* SERJ_PPARSE_H */

