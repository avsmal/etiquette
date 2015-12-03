#include <boost/python.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include <string>

#include "Setting.hpp"

#include <Python.h>

#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>


#include "MailBox.hpp"
#include "Message.hpp"
#include "../ui/cpp/NotifyMessage.hpp"
#include "Accounts.hpp"
#include "Setting.hpp"

namespace bp = boost::python;
using namespace boost::python;



namespace {
class AccountsPy {
public:
    AccountsPy(const std::string& country):
		accounts_(Setting("config.xml")) {

		vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();		
	}
    bp::list getNewMessages() {
		bp::list answer;
    	std::map <std::string, std::vector<Message>> map = accounts_.getUnAnswered();
    	for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
        	std::vector<Message> messages = itMap->second;

        	for (size_t i = 0; i < messages.size(); ++i) {
            	Message msg = messages[i];
            	bp::tuple tpl = bp::make_tuple(itMap->first, msg.getFrom());
            	answer.append(tpl);    
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
        .def("getNewMessages", &AccountsPy::getNewMessages)
    ;
}
