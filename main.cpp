#include <iostream>
#include <string>
#include <vmime/vmime.hpp>

#include "MailBox.hpp"
#include "Message.hpp"
#include "NotifyMessage.hpp"


	

inline void eatline() { while (std::cin.get() != '\n') continue; }

int main(void)
{
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


	MailBox c(login, password, server);
	c.connect();
	c.disconnect();
	c.connect();
	c.connect();
	std::vector<Message> s = c.getUnAnswered();
	for(size_t i = 0; i < s.size(); ++i)
	{
		Message msg = s[i];
		NotifyMessage nM(msg);
		nM.printNotify();
	}

	return 0;	
}



