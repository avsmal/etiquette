#pragma once
#include <vmime/vmime.hpp>
#include <string>

#include "Message.hpp"
#include "Folder.hpp"


class Folder
{
	public:

	enum FLAG_MESSAGE {SEEN, RECENT, REPLIED, DELETED, PASSED};
	//Constructor
	Folder(vmime::shared_ptr <vmime::net::folder> folder, std::string mod);
	//Methods
	Message get_message(int idMessage);
	size_t size();
	std::vector<Message> get_messages();
	std::vector<Message> get_messages(FLAG_MESSAGE flag);

	private:
	vmime::shared_ptr <vmime::net::folder> folder_;
};
