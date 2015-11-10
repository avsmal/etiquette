#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include "MailBox.hpp"
#include "Message.hpp"
#include "NotifyMessage.hpp"
#include "MailBoxSetting.hpp"
	

inline void eatline() { while (std::cin.get() != '\n') continue; }

int main(void)
{
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();

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
	try
	{
		mailbox.connect();
	
	}
	catch (vmime::exception& e)
    	{
        	std::cerr << "vmime::exception; " << e.what() << std::endl;
    	}
	std::vector<Message> messages = mailbox.getUnAnswered();
	for(size_t i = 0; i < messages.size(); ++i)
	{
		Message msg = messages[i];
		NotifyMessage notifyMessage(msg);
		notifyMessage.printNotify();
	}

	return 0;	
}



