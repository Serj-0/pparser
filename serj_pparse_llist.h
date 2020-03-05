#ifndef SERJ_PPARSE_LLIST_H
#define SERJ_PPARSE_LLIST_H
namespace serj{

//object to store unparsed data from file
struct unparsed_obj{
    void* object_data;
    unparsed_obj* next;
}*base_unprs_obj, *last_unprs_obj;

unparsed_obj* create_unparsed_object(void* data){
    last_unprs_obj->next = new unparsed_obj;
    last_unprs_obj = last_unprs_obj->next;
    last_unprs_obj->object_data = data;
    last_unprs_obj->next = nullptr;
}

void init_unparsed_objects(){
    base_unprs_obj = new unparsed_obj;
    base_unprs_obj->object_data = nullptr;
    base_unprs_obj->next = nullptr;
    last_unprs_obj = base_unprs_obj;
}

void destroy_unparsed_objects(){
    unparsed_obj* obj = base_unprs_obj, *nxt = nullptr;
    
    while(true){
        nxt = obj->next;
        delete static_cast<char*>(obj->object_data);
        std::cout << "DELETING " << obj << std::endl;
        delete obj;
        if(!nxt) break;
        obj = nxt;
    }
}

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

