#pragma once
#include <string>
#include <map>
#include <vector>

#include "Setting.hpp"
#include "MailBox.hpp"
#include "Message.hpp"


class Accounts {
public:
    Accounts(Setting const & setting);
    std::map <std::string, std::vector<Message>> getUnAnswered();
private:
    Setting setting_;
    std::vector<MailBox> mail_boxes_;
    MailBox makeMailBox_(TiXmlElement const * mailBoxXML);
};
