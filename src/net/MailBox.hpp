#pragma once
#include <string>
#include <vector>
#include <vmime/vmime.hpp>

#include "Message.hpp"
#include "MailBoxSetting.hpp"

class MailBox {
    public:

    //Constructor
    MailBox(MailBoxSetting const & mailBoxSetting);
    MailBox();
    //Methods    
    bool connect();
    bool disconnect();
    std::vector<Message> getUnAnswered();
    std::string const & getLogin() const;
    MailBox & operator =(const MailBox & other);
    ~MailBox();
    private:
    //Methods
    vmime::utility::url makeUrl_(std::string const & login,
                                 std::string const & password,
                                 std::string const & server);
    void                makeStore_(vmime::utility::url const & url);

    vmime::ref <vmime::net::store> store_;
    MailBoxSetting                 setting_;
};
