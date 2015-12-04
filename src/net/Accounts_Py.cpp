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
        list getNewMessages() {
            list answer;
            std::map <std::string, std::vector<Message>> map = accounts_.getUnAnswered();

            for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
                std::vector<Message> messages = itMap->second;

                for (size_t i = 0; i < messages.size(); ++i) {
                    Message msg = messages[i];
                    DateTime msg_date = msg.getDate();
                    tuple date = make_tuple(msg_date.Year, msg_date.Month,
                                            msg_date.Day,  msg_date.Hour,
                                            msg_date.Minute, msg_date.Second,
                                            msg_date.Zone);
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
