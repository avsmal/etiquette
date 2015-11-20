#include <string>
#include <map>
#include <vector>

#include "MailBox.hpp"
#include "Message.hpp"
#include "Accounts.hpp"


Accounts::Accounts(Setting const & setting):
    setting_(setting)
{}

std::map <std::string, std::vector<Message>> Accounts::getUnAnswered() {
    std::vector<MailBox> mailBoxes;
    std::map <std::string, std::vector<Message>> answer;
    TiXmlElement const * child = setting_.get("ddd.mailboxs.mailbox");

    for (child; child; child = child->NextSiblingElement()) {
		mailBoxes.push_back(makeMailBox_(child));
	}
    
    for (size_t i = 0; i < mailBoxes.size(); ++i) {
        mailBoxes[i].connect();
        answer.insert(std::pair<std::string,std::vector<Message>>(mailBoxes[i].getLogin(), mailBoxes[i].getUnAnswered()));
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
