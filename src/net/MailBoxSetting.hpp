#pragma once
#include <string>
#include <vector>
#include <vmime/vmime.hpp>

class MailBoxSetting
{
	public:
	MailBoxSetting(std::string login, std::string password, std::string server,
                   std::vector<std::string> const & ignored_folder_name);

	MailBoxSetting(MailBoxSetting const & mailBoxSetting);

	bool isIgnoredFolder(vmime::ref<vmime::net::folder> const & folder) const;
	
    std::string const & getLogin() const;
    std::string const & getPassword() const;
    std::string const & getServer() const;

	private:
	std::vector<std::string> ignored_folder_name_;
    std::string login_;
    std::string password_;
    std::string server_;
};
