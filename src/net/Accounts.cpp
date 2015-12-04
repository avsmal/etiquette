#include <string>
#include <map>
#include <vector>

#include "MailBox.hpp"
#include "Message.hpp"
#include "Accounts.hpp"

Accounts::Accounts(Setting const & setting):
    setting_(setting) {
    TiXmlElement const * child = setting_.get("ddd.mailboxs.mailbox");

    for (child; child; child = child->NextSiblingElement()) {
        mail_boxes_.push_back(makeMailBox_(child));
    }
}

std::map <std::string, std::vector<Message>> Accounts::getUnAnswered() {
    std::map <std::string, std::vector<Message>> answer;
    
    for (size_t i = 0; i < mail_boxes_.size(); ++i) {
        mail_boxes_[i].connect();
        auto pair = std::make_pair(mail_boxes_[i].getLogin(), 
                                   mail_boxes_[i].getUnAnswered());
        answer.insert(pair);
        mail_boxes_[i].disconnect();
    }
    return answer;
}

MailBox Accounts::makeMailBox_(TiXmlElement const * mailBoxXML) {
    std::string login = mailBoxXML->Attribute("login");
    std::string password = mailBoxXML->Attribute("password");
    std::string server = mailBoxXML->Attribute("server");
    
    std::vector<std::string> ignoredMailBox;
    ignoredMailBox.push_back("Spam");
    ignoredMailBox.push_back("Trash");
    ignoredMailBox.push_back("Sent");

    MailBoxSetting mailBoxSetting(login, password, server, ignoredMailBox);
    
    MailBox mailbox(mailBoxSetting);
    return mailbox;
}
