#include <vmime/vmime.hpp>
#include <string>
#include <iostream>

#include "Message.hpp"
#include "DateTime.hpp"

Message::Message(vmime::ref <vmime::net::message> const & msg,
                 vmime::ref <vmime::net::folder> const & folder):
    message_ptr_(msg), folder_ptr_(folder), is_set_date_(false)
{}
Message::Message(Message const & msg):
    folder_ptr_(msg.folder_ptr_), message_ptr_(msg.message_ptr_), is_set_date_(false) {
    from_ = msg.from_;
	subject_ = msg.subject_;
	date_ = msg.date_;
	from_ = msg.from_;
	body_ = msg.body_;
}
std::string const & Message::getFrom() const {    
    if(from_.empty())
    {        
        from_ = message_ptr_->getHeader()->From()->
                getValue().dynamicCast<const vmime::mailbox>()->getEmail();
    }
    return from_;
}

std::string const & Message::getSubject() const {
    if (subject_.empty()) {
        subject_ = message_ptr_->getHeader()->Subject()->
                   getValue().dynamicCast<const vmime::text>()->
                   getConvertedText(vmime::charset("utf-8"));
    }
    return subject_;
}

std::string const & Message::getBody() {
    if(body_.empty()) {
        vmime::string                             outString;
        vmime::utility::outputStreamStringAdapter out(outString);
        message_ptr_->extract(out);
        body_ = outString;
    }
    return body_;
}

DateTime const & Message::getDate() {
    if (!is_set_date_) {        
        auto s = message_ptr_->getHeader()->Date()->
                 getValue().dynamicCast<const vmime::datetime>();
        date_ = *s;
    }
    return date_;  
}

bool Message::isAnswered() const {
    if (message_ptr_->getFlags() & vmime::net::message::FLAG_REPLIED) {
        return true;
    }
    return false;
}
