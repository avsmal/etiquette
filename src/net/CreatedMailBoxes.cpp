#include <string>
#include <vector>

#include "CreatedMailBoxes.hpp"
#include "MailBox.hpp"
#include "MailBoxSetting.hpp"
#include "tinyxml.h"


CreatedMailBox::CreatedMailBox(std::string const & fileNameConfig):
	fileNameConfig_(fileNameConfig)
{}


std::vector<MailBox> CreatedMailBox::getMailBoxes() {
	std::vector<MailBox> answer;

	TiXmlDocument doc(fileNameConfig_.c_str());
	if (!doc.LoadFile()) {
		//exseption
		return answer;
	}
	TiXmlHandle docHandle(&doc);
	TiXmlElement* child = docHandle.FirstChild("ddd").FirstChild("mailboxs").FirstChild("mailbox").ToElement();

	for (child; child; child = child->NextSiblingElement()) {
		answer.push_back(makeMailBox_(child));
	}
	
	return answer;
}
MailBox CreatedMailBox::makeMailBox_(TiXmlElement* mailBoxXML) {
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


