#pragma once
#include<string>
#include<vector>
#include <vmime/vmime.hpp>


class MailBoxSetting
{
	public:
	MailBoxSetting(std::vector<std::string> const & ignored_folder_name);
	MailBoxSetting(MailBoxSetting const & mailBoxSetting);

	bool isIgnoredFolder(vmime::shared_ptr<vmime::net::folder> const & folder) const;
	
	private:
	std::vector<std::string> ignored_folder_name_;
};
