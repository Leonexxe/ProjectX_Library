#include <list>
#include <string>

class json_data
{
public:
    json_data(std::string val)
    {
        this->content = val;
    }

    /**
     * @brief indicates if the data is to be deleted, set to 1 to delete it, can be undone as long as the json object exists since data remains in RAM.
     */
    bool DELETE = 0;
    /**
     * @brief data from .json file
     */
    std::string content = "";
};