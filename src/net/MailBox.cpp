#include <string>
#include <vector>
#include <vmime/vmime.hpp>
#include <exception>
#include <iostream>

#include "timeoutHandler.hpp"
#include "Message.hpp"
#include "MailBox.hpp"
#include "MailBoxSetting.hpp"
#include "certificateVerifier.hpp"
#include "../../exception/exception.hpp"
        
static vmime::ref <vmime::net::session> g_session
    = vmime::create <vmime::net::session>();

MailBox::MailBox(MailBoxSetting const & mailBoxSetting):
    store_(nullptr),
    setting_(mailBoxSetting)
{}


MailBox::MailBox():
    store_(nullptr)
{}
vmime::utility::url MailBox::makeUrl_(std::string const & login,
                                      std::string const & password,
                                      std::string const & server) {
    std::string connectionString = "imaps://" + login + ":" + password
                                              + "@" + server;
    vmime::string urlString = connectionString;
    vmime::utility::url url(urlString);
    return url;
}
bool MailBox::connect() {
    if (store_) {
        return true;
    }
    int connection_attempt = 0;
    makeStore_(makeUrl_(setting_.getLogin(), setting_.getPassword(), setting_.getServer()));
    while (connection_attempt < 3) {
        try {
            std::cout << "Connect to: " << setting_.getLogin() << std::endl;
            store_->connect();
            return true;
        } catch (vmime::exceptions::connection_error & e) {
            ++connection_attempt;
        } catch (vmime::exceptions::authentication_error & e) {
            throw AuthenticationException();
        }
    }
    throw ConnectException();
}

bool MailBox::disconnect() {
    if (!store_) {
        try {
            store_->disconnect();
        } catch (std::exception &s) {
        }
        store_ = NULL;
    }
    return true;
}

void MailBox::makeStore_(vmime::utility::url const & url) {
    store_ = g_session->getStore(url);
    store_->setProperty("connection.tls", true);
    store_->setProperty("options.need-authentication", true);
    store_->setTimeoutHandlerFactory(vmime::create <timeoutHandlerFactory>());
    store_->setCertificateVerifier(vmime::create <interactiveCertificateVerifier>());
}

std::vector<Message> MailBox::getUnAnswered(const DateTime & from) {
    std::vector<Message> messages;
    std::cout << "Download messages";
    try {
        std::vector< vmime::ref<vmime::net::folder> > folders = store_->getRootFolder()->getFolders(true);
        for (auto folder : folders) {
            folder->open(vmime::net::folder::MODE_READ_ONLY);

            if (!setting_.isIgnoredFolder(folder)) {
                for (size_t i = folder->getMessageCount(); i >= 1; --i) {
                    std::cout << ".";
                    auto msgVmime = folder->getMessage(i);
                    folder->fetchMessage(msgVmime,
                        vmime::net::folder::FetchOptions::FETCH_FLAGS |
                        vmime::net::folder::FetchOptions::FETCH_ENVELOPE);
                    Message msg(msgVmime, folder);
                    if (msg.isAnswered()) {
                        continue;
                    }
                    if (msg.getDate() < from) {
                        break;
                    }   
                    messages.push_back(msg);
                }
            }
        }
    } catch (vmime::exception & e) {
        throw NetException();
    }
    std::cout << "done." << std::endl;
    return messages;
    
}
std::string const & MailBox::getLogin() const {
    return setting_.getLogin();
}
MailBox::~MailBox() {
    if (store_) {
        disconnect();
    }
}

MailBox & MailBox::operator =(const MailBox & other) {
    if (this != &other) {
        store_ = other.store_;
        setting_ = other.setting_;
    }
    return *this;
}
