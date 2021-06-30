#include <list>
#include <string>
#include "json_data.cpp"

class json_group
{
public:
    std::list<json_data> data;
    json_group(std::string Name, std::string Path)
    {
        this->name = Name;
        this->path = Path;
    }

    void _delete()
    {
    }
    void add(json_data* jd)
    {
        this->data.push_back(*jd);
    }
    std::string name;
    std::string path;
};
static json_group group_main(){return json_group("json","json");}