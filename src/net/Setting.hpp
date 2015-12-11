#pragma once
#include <string>

#include "tinyxml.h"

class Setting {
    public:
    //Constructor
    Setting(std::string const & configPath);
    Setting(Setting const & setting);
    //Methods
    TiXmlElement const * get(std::string const & path) const;
    std::string getString(std::string const & path) const;
    private:
    std::string configPath_;
    bool load_() const;
    mutable bool loaded_;
    mutable TiXmlDocument configFile_;      
};
