#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include <string>
#include <sstream>
#include <vector>
#include "serj_pparse_llist.h"
#include "serj_pparse_consts.h"

#define PPARSE_ERR_HEAD "[PPARSE ERROR]: "
#define PPARSE_LOG_ERR(x) std::cerr << PPARSE_ERR_HEAD << x
#define PPARSE_LOG_OBJ_ERR(x, y) std::cerr << PPARSE_ERR_HEAD << " obj: '" << x << "'\n\t\t" << y
using namespace std;

namespace serj{

//prepare pparse for usage
void pparse_init(){
    init_unparsed_objects();
    init_datasizes();
}

//exit pparse
void pparse_exit(){
    destroy_unparsed_objects();
}

//split string by delimiter
vector<string> split(string str, char delim){
    istringstream ist(str);
    string elem;
    vector<string> splits;
    while(getline(ist, elem, delim)){
        splits.push_back(elem);
    }
    return splits;
}

//get string from within braces\n
//e.g. "{content}" -> "content"
string uncase(string str, char lbrace, char rbrace){
    int fst = str.find_first_of(lbrace);
    int lbrc = 0;
    for(int i = fst + 1; i < str.size(); i++){
        lbrc += (str[i] == lbrace) - (str[i] == rbrace);
        if(lbrc < 0 && str[i] == rbrace){
            return str.substr(fst + 1, i - fst - 1);
        }
    }
    return str;
}

//cut first and last character from string
string trimcase(string str){
    return str.substr(1, str.size() - 1);
}

//parse file data to usable object
void pparse_object(string data){
    if(data[0] != '$'){
        PPARSE_LOG_OBJ_ERR(data, " Invalid object initial character.\n");
        return;
    }
    
    vector<string> bsizedef = split(data.substr(2, data.length() - data.find_first_of(">", 2, data.length())), ',');
    int bsize = 0;
    for(int i = 0; i < bsizedef.size(); i++){
        if(isalpha(bsizedef[i][0])){
            bsize += pparse_type_bytesizes[bsizedef[i]];
        }else{
            bsize += stoi(bsizedef[i]);
        }
    }
    cout << bsize << endl;
}

}

#endif /* SERJ_PPARSE_H */

