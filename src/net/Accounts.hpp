#pragma once
#include <string>
#include <map>

#include "Setting.hpp"
#include "MailBox.hpp"
#include "Message.hpp"


class Accounts {
    public:
    Accounts(Setting const & setting);
    std::map <std::string, std::vector<Message>> getUnAnswered();
    private:
    Setting setting_;
    MailBox makeMailBox_(TiXmlElement const * mailBoxXML);
};
