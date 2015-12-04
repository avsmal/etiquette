#include <string>
#include <vector>
#include <vmime/vmime.hpp>

#include "MailBoxSetting.hpp"


MailBoxSetting::MailBoxSetting(std::string const & login,
                               std::string const & password,
                               std::string const & server,
                               std::vector<std::string> const & ignored_folder_name) {
    ignored_folder_name_ = ignored_folder_name;
    login_ = login;
    password_ = password;
    server_ = server;
}
MailBoxSetting::MailBoxSetting(std::string login, std::string password, std::string server) {
    login_ = login;
    password_ = password;
    server_ = server;
}
MailBoxSetting::MailBoxSetting(MailBoxSetting const & mailBoxSetting) {
    ignored_folder_name_ = mailBoxSetting.ignored_folder_name_;
    login_ = mailBoxSetting.login_;
    password_ = mailBoxSetting.password_;
    server_ = mailBoxSetting.server_;
}
MailBoxSetting::MailBoxSetting() {
}
bool MailBoxSetting::isIgnoredFolder(vmime::ref<vmime::net::folder> const & folder) const {
    //O(n) -> O(log(n)) ?
    std::string folderName = folder->getFullPath().getLastComponent().generate();
    for (auto ignored_folder : ignored_folder_name_) {
        if(folderName == ignored_folder) {
            return true;
        }
    }
    return false;
}

std::string const & MailBoxSetting::getLogin() const {
    return login_;
}
std::string const & MailBoxSetting::getPassword() const {
    return password_;
}
std::string const & MailBoxSetting::getServer() const {
    return server_;
}

MailBoxSetting & MailBoxSetting::operator =(const MailBoxSetting & other) {
    if (this != &other) {
        ignored_folder_name_ = other.ignored_folder_name_;
        login_ = other.login_;
        password_ = other.password_;
        server_ = other.server_;
    }
    return *this;
}
