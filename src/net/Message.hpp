#pragma once
#include <vmime/vmime.hpp>
#include <string>
#include "DateTime.hpp"

class Message
{
	public:
	//Constructors
	Message(vmime::ref<vmime::net::message> const & msg, vmime::ref<vmime::net::folder> const & folder);
	Message(Message const & msg);
	
	//Methods
	std::string const & getFrom() const;
	std::string const & getSubject() const;
	std::string const & getBody();
    DateTime    const & getDate();
	bool isAnswered() const;

	private:
	vmime::ref<vmime::net::folder>  folder_ptr_;
	vmime::ref<vmime::net::message> message_ptr_;
	mutable std::string from_;
	mutable std::string subject_;
	mutable std::string body_;
    mutable DateTime    date_;
    bool                is_set_date_;
};
