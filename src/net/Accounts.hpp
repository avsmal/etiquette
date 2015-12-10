#pragma once
#include <string>
#include <map>
#include <vector>

#include "Setting.hpp"
#include "MailBox.hpp"
#include "Message.hpp"
#include "DateTime.hpp"
    
class Accounts {
public:
    Accounts(Setting const & setting);
    std::map <std::string, std::vector<Message>> getUnAnswered(const DateTime & from);
private:
    bool connectMailBox_(MailBox & mailBox);
    Setting setting_;
    std::vector<MailBox> mail_boxes_;
    MailBox makeMailBox_(TiXmlElement const * mailBoxXML);
};
