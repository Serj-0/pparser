#ifndef SERJ_PPARSE_LLIST_H
#define SERJ_PPARSE_LLIST_H
namespace serj{

//object created directly from file data
struct unparsed_obj{
    void* object_data;
    unparsed_obj* next;
}*base_unprs_obj, *last_unprs_obj;

//create new object of unparsed data
unparsed_obj* create_unparsed_object(void* data){
    last_unprs_obj->next = new unparsed_obj;
    last_unprs_obj = last_unprs_obj->next;
    last_unprs_obj->object_data = data;
    last_unprs_obj->next = nullptr;
}

//initialize unparsed objects linked list
void init_unparsed_objects(){
    base_unprs_obj = new unparsed_obj;
    base_unprs_obj->object_data = nullptr;
    base_unprs_obj->next = nullptr;
    last_unprs_obj = base_unprs_obj;
}

//deallocate unparsed objects
void destroy_unparsed_objects(){
    unparsed_obj* obj = base_unprs_obj, *nxt = nullptr;
    
    while(true){
        nxt = obj->next;
        delete static_cast<char*>(obj->object_data);
//        std::cout << "DELETING " << obj << std::endl;
        delete obj;
        if(!nxt) break;
        obj = nxt;
    }
}

//get unparsed object by index
unparsed_obj* get_unparsed_obj(int index){
    unparsed_obj* obj = base_unprs_obj;
    while(index-- > 0){
        if(!obj->next) return obj;
        obj = obj->next;
    }
    return obj;
}

}

#endif /* SERJ_PPARSE_LLIST_H */
