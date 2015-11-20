#include <string>
#include "tinyxml.h"

#include "Setting.hpp"

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
