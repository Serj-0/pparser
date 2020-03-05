#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include <string>
#include <sstream>
#include <vector>
#include "serj_pparse_llist.h"

#define PPARSE_ERR_HEAD "[PPARSE ERROR]: "
#define PPARSE_LOG_ERR(x) std::cerr << PPARSE_ERR_HEAD << x
#define PPARSE_LOG_OBJ_ERR(x, y) std::cerr << PPARSE_ERR_HEAD << " obj: '" << x << "'\n\t\t" << y
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

//split string by delimiter
vector<string> split(string& str, char delim){
    istringstream ist(str);
    string elem;
    vector<string> splits;
    while(getline(ist, elem, delim)){
        splits.push_back(elem);
    }
    return splits;
}

//get string from within braces\n
//e.g. "<content>" -> "content"
string uncase(string str, char lbrace, char rbrace){
    int li = str.find_first_of(lbrace);
    return str.substr(li + 1, str.find_last_of(rbrace) - li - 1);
}

//parse file data to usable object
void pparse_object(string data){
    if(data[0] != '$'){
        PPARSE_LOG_OBJ_ERR(data, " Invalid object initial character.\n");
        return;
    }
    
    int bsize = stoi(data.substr(2, data.length() - data.find_first_of(">", 2, data.length())));
    cout << bsize;
}

}

#endif /* SERJ_PPARSE_H */

