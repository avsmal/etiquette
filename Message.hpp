#pragma once
#include <vmime/vmime.hpp>
#include <string>

class Message
{
	public:
	Message(vmime::shared_ptr<vmime::net::message> msg, vmime::shared_ptr<vmime::net::folder> folder);
	Message(Message const & msg);
	//TODO: возвращать const ссылки
	//TODO: добавить const у методов
	//TODO: ленивая инициализация полей from и subject
	std::string getFrom();
	std::string getSubject();
	std::string getBody();
	bool isAnswered();
	private:
	vmime::shared_ptr<vmime::net::folder>  folder_ptr_;
	vmime::shared_ptr<vmime::net::message> message_ptr_;
};
