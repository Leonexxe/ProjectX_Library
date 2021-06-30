#include "json_group.cpp"
#include <projectX/sysout/sysout.cpp>

class json
{
public:
    json_group JSON = group_main();
    json(const char data[])
    {
        sysInfo("parsing json...");
        for(int i = 0;i < sizeof(data);i++)
        {
            char c = data[i];
            sysInfo("parsing "+std::to_string(c)+"...");
            switch(c)
            {
                case('{'):this->openGroup();                   break;// open group
                case('}'):this->closeGroup();                  break;// close groups
                case('"'):                                     break;// open/close data
                case(','):this->newData();                     break;// open new data object
                case(':'):this->init_value();                  break;// 
                default:this->data_latest += std::to_string(c);break;// collect data
            }
        }
    }
    void print()
    {
    }
private:
    std::list<json_group> groups_nested;
    int context = 1;
    std::string data_latest = "";
    void openGroup()
    {
        if(this->context == 1)
        {
            std::string p = "";
            for(json_group I : this->groups_nested)
            {
                p.push_back('/');
                p=p+I.name;
            }
            p.push_back('/');
            p=p+this->data_latest;
            sysInfo("creating group: " + this->data_latest + ":"+p);
            json_group jGroup(this->data_latest,p);
            this->groups_nested.push_front(jGroup);
        }
    }
    void closeGroup() 
    {
    }
    void open_close_data()
    {
    }
    void newData()
    {
    }
    void init_value()
    {
        this->context = 1;
    }
};
