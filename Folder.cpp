#include "MailBox.hpp"
#include "Folder.hpp"
#include "Message.hpp"


Folder::Folder(vmime::shared_ptr <vmime::net::folder> folder, std::string mod)
{	
	folder_ = folder;
	if(mod == "w")
	{
		folder_->open(vmime::net::folder::MODE_READ_WRITE);
	}
	else if (mod == "r")
	{
		folder_->open(vmime::net::folder::MODE_READ_ONLY);
	}
}

Message Folder::get_message(int id_message)
{
	vmime::shared_ptr <vmime::net::message> msg = folder_->getMessage(id_message);
	folder_->fetchMessage(msg, vmime::net::fetchAttributes::FLAGS |  vmime::net::fetchAttributes::ENVELOPE);
	return Message(msg);
}

size_t Folder::size()
{
	return folder_->getMessageCount();
}

std::vector<Message> Folder::get_messages()
{
	std::vector<Message> answer;
	for(size_t i = 1; i <= this->size(); ++i)
	{
		answer.push_back(this->get_message(i));
	}
	return answer;
}
