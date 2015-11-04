#include<string>
#include<vector>
#include <vmime/vmime.hpp>

#include "MailBoxSetting.hpp"


MailBoxSetting::MailBoxSetting(std::vector<std::string> const & ignored_folder_name)
{
	ignored_folder_name_ = ignored_folder_name;
}
MailBoxSetting::MailBoxSetting(MailBoxSetting const & mailBoxSetting)
{
	ignored_folder_name_ = mailBoxSetting.ignored_folder_name_;
}

bool MailBoxSetting::isIgnoredFolder(vmime::shared_ptr<vmime::net::folder> const & folder) const
{
	//O(n) -> O(log(n)) ?
	std::string folderName = folder->getFullPath().toString("/",  vmime::charset::getLocalCharset());
	for (auto ignored_folder : ignored_folder_name_)
	{
		if(folderName == ignored_folder)
		{
			return true;
		}
	}
	return false;
}
