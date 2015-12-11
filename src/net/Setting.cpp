#include <string>
#include "tinyxml.h"

#include "Setting.hpp"
#include <iostream>
Setting::Setting(std::string const & configPath):
    configPath_(configPath), loaded_(false)
{}
Setting::Setting(Setting const & setting):
    configPath_(setting.configPath_), loaded_(false)
{}
bool Setting::load_() const {
    TiXmlDocument doc(configPath_.c_str());
    configFile_ = doc;
    return loaded_ = configFile_.LoadFile();
}

TiXmlElement const * Setting::get(std::string const & path) const {
    if (!loaded_) {
        load_();
    }

    TiXmlHandle docHandle(&configFile_); 
    std::string partPath = "";
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] != '.') {
            partPath.push_back(path[i]);
            continue;
        }
        docHandle = docHandle.FirstChild(partPath.c_str());
        partPath = "";        
    }
    return docHandle.FirstChild(partPath.c_str()).ToElement();
}


std::string Setting::getString(std::string const & path) const {
    std::string new_path;
    std::string attribute;
    for (size_t i = path.size() - 1; i >= 0; --i) {
        if (path[i] == '.') {
            new_path = path.substr(0, i);
            attribute = path.substr(i + 1, path.size());
            break;
        }
    }
    return this-> get(new_path)->Attribute(attribute.c_str());   
}
