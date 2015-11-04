#pragma once
#include <vmime/vmime.hpp>
#include <string>

class Message
{
	public:
	//Constructors
	Message(vmime::shared_ptr<vmime::net::message> const & msg, vmime::shared_ptr<vmime::net::folder> const & folder);
	Message(Message const & msg);
	
	//Methods
	std::string const & getFrom() const;
	std::string const & getSubject() const;
	std::string const & getBody() const ;
	bool isAnswered() const;

	private:
	vmime::shared_ptr<vmime::net::folder>  folder_ptr_;
	vmime::shared_ptr<vmime::net::message> message_ptr_;
	mutable std::string from_;
	mutable std::string subject_;
	mutable std::string body_;
};
