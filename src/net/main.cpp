#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include "MailBox.hpp"
#include "Message.hpp"
#include "../ui/cpp/NotifyMessage.hpp"
#include "MailBoxSetting.hpp"
#include "Setting.hpp"
#include "Accounts.hpp"	

inline void eatline() { while (std::cin.get() != '\n') continue; }

int main(void) {
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
	Setting s("config.xml");
	Accounts acc(s);
    std::map <std::string, std::vector<Message>> map = acc.getUnAnswered();
	int k = 0;
    for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
         std::vector<Message> messages = itMap->second;

         for (size_t i = 0; i < messages.size(); ++i) {
			Message msg = messages[i];
			NotifyMessage notifyMessage(msg);
			notifyMessage.printNotify();
			std::cout << messages[i].getFrom() << std::endl;
		}
    }
	return 0;	
}



