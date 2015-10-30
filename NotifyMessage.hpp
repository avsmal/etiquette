#pragma once
#include "Message.hpp"


class NotifyMessage {
	public:
		NotifyMessage(Message msg);
		void printNotify();
	private:
		Message msg_;
};
