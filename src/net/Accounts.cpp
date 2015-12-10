#include <string>
#include <map>
#include <vector>

#include "MailBox.hpp"
#include "Message.hpp"
#include "Accounts.hpp"
#include "../../exception/exception.hpp"
#include "DateTime.hpp"

Accounts::Accounts(Setting const & setting):
    setting_(setting) {
    TiXmlElement const * child = setting_.get("ddd.mailboxs.mailbox");

    for (child; child; child = child->NextSiblingElement()) {
        mail_boxes_.push_back(makeMailBox_(child));
    }
}

std::map <std::string, std::vector<Message>> Accounts::getUnAnswered(const DateTime & from) {
    std::map <std::string, std::vector<Message>> answer;
    
    for (size_t i = 0; i < mail_boxes_.size(); ++i) {
        int n = 0;
        while (n < 3) {
            if (!this->connectMailBox_(mail_boxes_[i])) {
                break;
            }
            try {
                auto pair = std::make_pair(mail_boxes_[i].getLogin(), mail_boxes_[i].getUnAnswered(from));
                answer.insert(pair);
                mail_boxes_[i].disconnect();
                break;
            } catch (NetException & e) {
                n++;
                mail_boxes_[i].disconnect();
                continue;
            }
        }
        if (n == 3) {
            std::cerr << "Сan not retrieve messages from the mailbox:" << mail_boxes_[i].getLogin() <<"." << std::endl;
        }       
    }
    return answer;
}

bool Accounts::connectMailBox_(MailBox & mailBox) {
    try {
            mailBox.connect();
            return true;
    } catch (ConnectException & e) {
            std::cerr << "Unable to connect:" << mailBox.getLogin() <<"." << std::endl;
            return false;
    } catch (AuthenticationException & e) {
            return false;
            std::cerr << "Unable to connect:" << mailBox.getLogin() << ". Incorrect login or password."<< std::endl;
    }
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
