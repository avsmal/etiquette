#pragma once
#include <string>
#include <vector>
#include <vmime/vmime.hpp>

#include "Message.hpp"
#include "MailBoxSetting.hpp"


class MailBox
{
	public:

	//Constructor
	MailBox(std::string const & userName, std::string const & userPassword, std::string const & serverAddress, MailBoxSetting const & mailBoxSetting);
	//Methods	
	bool connect();
	bool disconnect();
	std::vector<Message> getUnAnswered();

	~MailBox();

	private:
	//Methods
	vmime::utility::url makeUrl_(std::string const & userPassword, std::string const & userName, std::string const & serverAddress);
	void                makeStore_(vmime::utility::url const & url);

	vmime::shared_ptr <vmime::net::store>                 store_;
	vmime::utility::url                   	              url_;
	MailBoxSetting                                        setting_;
};
