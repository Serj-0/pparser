#ifndef SERJ_PPARSE_LLIST_H
#define SERJ_PPARSE_LLIST_H
#include <map>

namespace serj{
using namespace std;

//object created directly from file data
struct uncasted_obj{
    string object_string;
    string object_label;
    map<string, int> object_data_counts;
    void* object_data;
    uncasted_obj* next;
}*base_uncst_obj, *last_uncst_obj;
int pparse_uncasted_obj_count;

//create new object of uncasted data
uncasted_obj* create_uncasted_object(void* data){
    last_uncst_obj->next = new uncasted_obj;
    last_uncst_obj = last_uncst_obj->next;
    last_uncst_obj->object_data = data;
    last_uncst_obj->next = nullptr;
    pparse_uncasted_obj_count++;
}

//create new object of uncasted data with bsize bytes of memory
uncasted_obj* create_uncasted_object(int bsize){
    last_uncst_obj->next = new uncasted_obj;
    last_uncst_obj = last_uncst_obj->next;
    last_uncst_obj->object_data = new char[bsize];
    last_uncst_obj->next = nullptr;
    pparse_uncasted_obj_count++;
}

//initialize uncasted objects linked list
void init_uncasted_objects(){
    base_uncst_obj = new uncasted_obj;
    base_uncst_obj->object_data = nullptr;
    base_uncst_obj->next = nullptr;
    last_uncst_obj = base_uncst_obj;
    pparse_uncasted_obj_count = 0;
    base_uncst_obj->object_string = "Uncasted Object List Base";
    base_uncst_obj->object_label = "Uncasted Object List Base";
}

//deallocate uncasted objects
void destroy_uncasted_objects(){
    uncasted_obj* obj = base_uncst_obj, *nxt = nullptr;
    
    while(true){
        nxt = obj->next;
        delete static_cast<char*>(obj->object_data);
//        cout << "DELETING " << obj << endl;
        delete obj;
        if(!nxt) break;
        obj = nxt;
    }
}

//get uncasted object by index
uncasted_obj* get_uncasted_obj(int index){
    uncasted_obj* obj = base_uncst_obj;
    while(index-- > 0){
        if(!obj->next) return obj;
        obj = obj->next;
    }
    return obj;
}

//return uncasted object by label
uncasted_obj* get_uncasted_obj(string label){
    uncasted_obj* obj = base_uncst_obj;
    do{
        obj = obj->next;
        if(obj->object_label == label){
            return obj;
        }
    }while(obj->next);
    return nullptr;
}

}

#endif /* SERJ_PPARSE_LLIST_H */
