#pragma once
#include <string>

#include "tinyxml.h"

class Setting {
    public:
    Setting(std::string const & configPath);
    Setting(Setting const & setting);
    TiXmlElement const * get(std::string const & path) const;
    
    private:
    std::string configPath_;
    bool load_() const;
    mutable bool loaded_;
    mutable TiXmlDocument configFile_;      
};
