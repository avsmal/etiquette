#include <iostream>
#include <string>
#include <vmime/vmime.hpp>

#include "MailBox.hpp"
#include "Message.hpp"
#include "NotifyMessage.hpp"
#include "MailBoxSetting.hpp"

	

inline void eatline() { while (std::cin.get() != '\n') continue; }

int main(void)
{

	//TODO: где обработка исключение из сетевой части?
	std::string login;
	std::string password;
	std::string server;
	
	std::cout << "Login:";
	std::cin >> login;
	eatline();
	std::cout << "Password:";
	std::cin >> password;
	eatline();
	std::cout << "Server:";
	std::cin >> server;
	eatline();

	std::vector<std::string> ignoredMailBox;
	ignoredMailBox.push_back("Spam");
	ignoredMailBox.push_back("Trash");
	ignoredMailBox.push_back("Sent");

	MailBoxSetting mailBoxSetting(ignoredMailBox);


	MailBox mailbox(login, password, server, mailBoxSetting);
	mailbox.connect();
	std::vector<Message> messages = mailbox.getUnAnswered();
	for(size_t i = 0; i < messages.size(); ++i)
	{
		Message msg = messages[i];
		NotifyMessage notifyMessage(msg);
		notifyMessage.printNotify();
	}

	return 0;	
}



