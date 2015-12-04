#include <boost/python.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include <string>
#include <map>
#include <vector>
#include <Python.h>
#include <iostream>

#include "Setting.hpp"
#include "MailBox.hpp"
#include "Message.hpp"
#include "Accounts.hpp"
#include "DateTime.hpp"


namespace {
    using namespace boost::python;

    class AccountsPy {
    public:
        AccountsPy(const std::string& country):
            accounts_(Setting("config.xml")) {
            std::cout << "constructor" << std::endl;
            vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();		
	    }
        list getNewMessages() {
            list answer;
            std::map <std::string, std::vector<Message>> map = accounts_.getUnAnswered();

            for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
                std::vector<Message> messages = itMap->second;

                for (size_t i = 0; i < messages.size(); ++i) {
                    Message msg = messages[i];
                    tuple date = make_tuple(msg.getDate().Year, msg.getDate().Month, msg.getDate().Day, msg.getDate().Hour, msg.getDate().Minute, msg.getDate().Second, msg.getDate().Zone);
                    tuple tpl = make_tuple(itMap->first, msg.getFrom());
                    list entry;
                    entry.append(tpl);
                    entry.append(date);                    
                    answer.append(entry);    
                }
            }
            return answer;
        }
    private:
        Accounts accounts_;
    };

}


BOOST_PYTHON_MODULE(accounts) {
    class_<AccountsPy>("AccountsPy", init<std::string>())
        .def("getMessages", &AccountsPy::getNewMessages)
    ;
}
