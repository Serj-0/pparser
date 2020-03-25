#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "serj_pparse_llist.h"
#include "serj_pparse_consts.h"
using namespace std;

#define PPARSE_ERR_HEAD "[PPARSE ERROR]: "
#define PPARSE_LOG_ERR(x) std::cerr << PPARSE_ERR_HEAD << x
#define PPARSE_LOG_OBJ_ERR(x, y) std::cerr << PPARSE_ERR_HEAD << " obj:  '" << x << "'\n\t\t" << y
#define PPARSE_LOG_HEAD "[PPARSE LOG]: "
#define PPARSE_LOG(x) std::cout << PPARSE_LOG_HEAD << x << std::endl

//cast last uncasted object to an object type
#define pparse_cast(type) *static_cast<type*>(last_uncst_obj->object_data)

namespace serj{

//prepare pparse for usage
void pparse_init(){
    init_uncasted_objects();
    init_datasizes();
}

//exit pparse
void pparse_exit(){
    destroy_uncasted_objects();
}

//parse file data to usable objects
void pparse_object(string data, string label = "No Label"){
    if(data[0] != '$'){
        PPARSE_LOG_OBJ_ERR(data, "Invalid object initial character.\n");
        return;
    }
    
    //get architecture of object
    vector<string> bsizedefstr = split(uncase(data, '<', '>'), ',');
    vector<string> bsizedef;

    int bsize = 0;
    for(int i = 0; i < bsizedefstr.size(); i++){
        if(isalpha(bsizedefstr[i][0])){
            vector<string> bsdfp = split(bsizedefstr[i], '_');
            int ss = 1;
            if(bsdfp.size() > 1) ss = stoi(bsdfp[1]);
            bsize += pparse_typesizes[bsdfp[0]] * ss;
            bsizedef.insert(bsizedef.end(), ss, bsdfp[0]);
        }else{
            bsize += stoi(bsizedefstr[i]);
        }
    }
    
    create_uncasted_object(bsize);
    last_uncst_obj->object_string = data;
    last_uncst_obj->object_label = label;
    char* objdata = static_cast<char*>(last_uncst_obj->object_data);
    
    //strip outermost braces
    data = uncase(data, '{', '}');
    vector<string> datas = split(data, ',');
    
    void* v = new char;
    int s, rep, di = 0;
    string sdfstr;
    
    for(int i = 0; i < bsizedef.size(); di++){
        delete static_cast<char*>(v);
        sdfstr = bsizedef[i];
        
        vector<string> dtsp = split(datas[di], '_');
        string dato = dtsp[0];
        
        if(dtsp.size() > 1){
            rep = stoi(dtsp[1]);
        }else{
            rep = 1;
        }

        s = pparse_typesizes[sdfstr];
        if(sdfstr == "string"){
            v = new string;
        }else{
            v = new char[s];
        }
        //actual data parse
        pparse_typefuncs[sdfstr](dato, v);
        for(int rr = 0; rr < rep; rr++){
            for(int j = 0; j < s; j++){
                *objdata = static_cast<char*>(v)[j];
                objdata++;
            }
        }
        
        i += rep;
    }
    
    delete static_cast<char*>(v);
}

void pparse_file(string path){
    ifstream ist(path);
    string label = "No Label";
    string comment;
    
    ostringstream obj("");
    
    char c = 0, prevc;
    int lb = 0;
    bool objective = false;
    string strb;

    map<string, string> tdefs;
    vector<string> keys;
    bool instr = false;
    
    while(prevc = c, ist.get(c)){
        if(c == '$'){
            objective = true;
            obj << c;
            getline(ist, strb, '{');
            obj << strb;
            obj << '{';
            lb = 0;
            continue;
        }else if(prevc != '\\' && c == '"'){
            instr = !instr;
            continue;
        }else if(!instr && (c == ' ' || c == '\n' || c == '\t')){
            continue;
        }else if(c == '?'){
            getline(ist, label);
            continue;
        }else if(c == '#'){
            getline(ist, comment);
            PPARSE_LOG("File comment: '" << comment << "'");
            continue;
        }else if(c == '!'){
            ist >> strb;
            string def;
            ist.ignore(1);
            getline(ist, def);
            keys.push_back(strb);
            tdefs.insert({strb, def});
            PPARSE_LOG("File text macro: " << strb << " -> " << def);
        }
        
        if(objective){
            if(c == '{'){
                lb++;
            }else if(c == '}'){
                lb--;
            }
            
            obj << c;
            if(lb == -1){
                objective = false;
                strb = obj.str();
                
                for(int i = 0; i < keys.size(); i++){
                    string dd = tdefs[keys[i]];
                    while(replace(strb, keys[i], dd)){}
                }
                
                pparse_object(strb, label);
                label = "No Label";
                obj = ostringstream("");
            }
        }
    }
    
    ist.close();
}

}

#endif /* SERJ_PPARSE_H */

