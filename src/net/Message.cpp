#include <vmime/vmime.hpp>
#include <string>

#include "Message.hpp"

Message::Message(vmime::ref <vmime::net::message> const & msg, vmime::ref <vmime::net::folder> const & folder):
	message_ptr_(msg), folder_ptr_(folder)
{}
Message::Message(Message const & msg):
	folder_ptr_(msg.folder_ptr_), message_ptr_(msg.message_ptr_)
{}
std::string const & Message::getFrom() const
{	
	if(from_.empty())
	{		
		from_ = message_ptr_->getHeader()->From()->getValue().dynamicCast<const vmime::mailbox>()->getEmail();
	}
	return from_;
}

std::string const & Message::getSubject() const
{
	if(subject_.empty())
	{
		subject_ = message_ptr_->getHeader()->Subject()->getValue().dynamicCast<const vmime::text>()->getConvertedText(vmime::charset("utf-8"));
	}
	return subject_;
}

std::string const & Message::getBody() 
{
	if(body_.empty())
	{
		vmime::string                             outString;
		vmime::utility::outputStreamStringAdapter out(outString);

		vmime::messageParser parsedMessage(message_ptr_->getParsedMessage());
		//parsedMessage.getTextPartList()[0]->getText()->extract(out);
		//body_ = outString;
	}
	return body_; //?
}
bool Message::isAnswered() const
{
	if(message_ptr_->getFlags() & vmime::net::message::FLAG_REPLIED)
	{
		return true;
	}
	return false;
}
