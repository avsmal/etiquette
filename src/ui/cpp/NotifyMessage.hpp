#pragma once
#include "../../net/Message.hpp"

class NotifyMessage {
    public:
        NotifyMessage(Message const & msg);
        void printNotify();
    private:
        Message msg_;
};
