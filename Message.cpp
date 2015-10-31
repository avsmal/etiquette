#include <vmime/vmime.hpp>
#include <string>

#include "Message.hpp"

Message::Message(vmime::shared_ptr <vmime::net::message> msg, vmime::shared_ptr <vmime::net::folder> folder):
	message_ptr_(msg), folder_ptr_(folder)
{}
Message::Message(Message const & msg):
	folder_ptr_(msg.folder_ptr_), message_ptr_(msg.message_ptr_)
{}
std::string Message::getFrom()
{
	return message_ptr_->getHeader()->From()->getValue<vmime::mailbox>()->getEmail().toString();
}

std::string Message::getSubject()
{
	return message_ptr_->getHeader()->Subject()->getValue<vmime::text>()->getConvertedText(vmime::charset("utf-8"));
}

std::string Message::getBody()
{
	vmime::string                             outString;
	vmime::utility::outputStreamStringAdapter out(outString);

	vmime::messageParser parsedMessage(message_ptr_->getParsedMessage());
	parsedMessage.getTextPartList()[0]->getText()->extract(out);
	return outString; //?
}
bool Message::isAnswered()
{
	if(message_ptr_->getFlags() & vmime::net::message::FLAG_REPLIED)
	{
		return true;
	}
	return false;
}
