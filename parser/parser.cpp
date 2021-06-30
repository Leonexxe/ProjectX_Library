#include <string>
#include <projectX/tools/strings.cpp>

class parsed
{
public:
    std::string funct = "";
    std::list<std::string> parameters;
    parsed(std::string S)
    {
        int i = 0;
        std::list<std::string> strlst = split(S,"<");
        std::string strarr[strlst.size()];i = 0;for(std::string I : strlst){strarr[i++] = I;}
        strlst = split(strarr[0],">");
        std::string strarr2[strlst.size()];i = 0;for(std::string I : strlst){strarr2[i++] = I;}
        strlst = split(strarr2[0],":");
        std::string strarr3[strlst.size()];i = 0;for(std::string I : strlst){strarr3[i++] = I;}
        funct = strarr3[0];
        std::string strparams = strarr3[1];
        std::string strvalues = strarr3[2];
        strlst = split(strvalues.substr(1,strvalues.substr(1).length() - 1),",");std::string values[strlst.size()];i = 0;for(std::string I : strlst){values[i++] = I;}
        //linking name and value together
        i = 0;
        for(std::string I : values)
        {
        }
    }
};

static parsed parse(std::string S){return parsed(S);}