#include <boost/python.hpp>
#include "Accounts.hpp"

namespace bp = boost::python;


class AccountPy {
public:
    AccountPy();
    bp::list getNewMessages();
private:
    Accounts accounts_;
};
