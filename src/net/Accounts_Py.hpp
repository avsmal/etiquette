#include <boost/python.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include <string>

#include "Accounts.hpp"
namespace bp = boost::python;


class AccountsPy {
public:
    AccountsPy(const std::string& country);
    bp::list getNewMessages();
private:
    Accounts accounts_;
};
