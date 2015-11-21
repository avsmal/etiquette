#pragma once
#include <string>
#include <vector>
#include <vmime/vmime.hpp>

//TODO: ссылки у std::string
class MailBoxSetting
{
	public:
	MailBoxSetting(std::string login, std::string password, std::string server,
                   std::vector<std::string> const & ignored_folder_name);
	
	MailBoxSetting(std::string login, std::string password, std::string server);
	MailBoxSetting(MailBoxSetting const & mailBoxSetting);
	MailBoxSetting();
	
	bool isIgnoredFolder(vmime::ref<vmime::net::folder> const & folder) const;
	
    std::string const & getLogin() const;
    std::string const & getPassword() const;
    std::string const & getServer() const;
	MailBoxSetting & operator=(MailBoxSetting const & other);

	private:
	std::vector<std::string> ignored_folder_name_;
    std::string login_;
    std::string password_;
    std::string server_;
};
