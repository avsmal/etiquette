#include <string>
#include <vector>
#include <vmime/vmime.hpp>

#include "authenticator.hpp"
#include "certificateVerifier.hpp"
#include "timeoutHandler.hpp"
#include "tracer.hpp"

#include "Message.hpp"
#include "MailBox.hpp"


static vmime::shared_ptr <vmime::net::session> g_session
	= vmime::make_shared <vmime::net::session>();

MailBox::MailBox(std::string const & userName, std::string const & userPassword, std::string const & serverAddress) :
	url_(makeUrl_(userName, userPassword, serverAddress)), store_(nullptr)
{}

vmime::utility::url MailBox::makeUrl_(std::string const & userName, std::string const & userPassword, std::string const & serverAddress)
{
	std::string connectionString = "imaps://" + userName + ":" + userPassword + "@" + serverAddress;
	vmime::string urlString = connectionString;
	vmime::utility::url url(urlString);
	return url;
}
bool MailBox::connect()
{
	//??
	if(!store_)
	{
		makeStore_(url_);
		store_->connect();
	}
	return true;
}

bool MailBox::disconnect()
{
	if(!store_)
	{
		store_->disconnect();
		store_.reset();
	}
	return true;
}
void MailBox::makeStore_(vmime::utility::url url)
{
	store_ = g_session->getStore(url);
	store_->setProperty("connection.tls", true);
	
	store_->setTimeoutHandlerFactory(vmime::make_shared <timeoutHandlerFactory>());
	
	store_->setCertificateVerifier(vmime::make_shared <interactiveCertificateVerifier>());

	vmime::shared_ptr <std::ostringstream> traceStream = vmime::make_shared <std::ostringstream>();
	store_->setTracerFactory(vmime::make_shared <myTracerFactory>(traceStream));
}

std::vector<Message> MailBox::getUnAnswered()
{
	std::vector<Message> messages;
	std::vector< vmime::shared_ptr<vmime::net::folder> > folders = store_->getRootFolder()->getFolders(true);
	for (auto folder : folders)
	{
		folder->open(vmime::net::folder::MODE_READ_ONLY);
		if(valuableFolder_(folder))
		{
			for(size_t i = 1; i <= folder->getMessageCount(); ++i)
			{
				auto msgVmime = folder->getMessage(i);
				folder->fetchMessage(msgVmime, vmime::net::fetchAttributes::FLAGS | vmime::net::fetchAttributes::ENVELOPE);
				Message msg(msgVmime, folder);
				if (msg.isAnswered())
				{
					continue;
				}
				messages.push_back(msg);
			}
		}
	}
	return messages;
	
}
bool MailBox::valuableFolder_(vmime::shared_ptr<vmime::net::folder> folder)
{
	std::string folderName = folder->getFullPath().toString("/",  vmime::charset::getLocalCharset());
	if(folderName == "Spam" || folderName == "Trash" || folderName == "Sent")
	{
		return false;
	}
	return true;
}

MailBox::~MailBox()
{
	if(store_)
	{
		disconnect();
	}
}
