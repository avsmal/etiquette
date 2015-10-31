#pragma once
#include "Message.hpp"


class NotifyMessage {
	public:
        //TOOD: const &
		NotifyMessage(Message msg);
		void printNotify();
	private:
		Message msg_;
};
