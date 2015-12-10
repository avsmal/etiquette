#include <boost/python.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include <string>
#include <map>
#include <vector>
#include <Python.h>

#include "Setting.hpp"
#include "MailBox.hpp"
#include "Message.hpp"
#include "Accounts.hpp"
#include "DateTime.hpp"

    
namespace {
    using namespace boost::python;

    class AccountsPy {
    public:
        AccountsPy(const std::string& path):
            accounts_(Setting(path)) {
            vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();        
        }
        list getNewMessages(int time_t) {
            list answer;
            DateTime s(time_t);
            std::map <std::string, std::vector<Message>> map = accounts_.getUnAnswered(s);

            for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
                std::vector<Message> messages = itMap->second;

                for (size_t i = 0; i < messages.size(); ++i) {
                    Message msg = messages[i];
                    DateTime msg_date = msg.getDate();
                    tuple date = make_tuple(msg_date.getYear(), msg_date.getMonth(),
                                            msg_date.getDay(),  msg_date.getHour(),
                                            msg_date.getMinute(), msg_date.getSecond(),
                                            msg_date.getZone());
                    list entry;
                    entry.append(make_tuple(itMap->first, msg.getFrom()));
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
