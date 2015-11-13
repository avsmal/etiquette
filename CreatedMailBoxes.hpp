#pragma once
#include <string>
#include <vector>

#include "MailBox.hpp"
#include "tinyxml.h"

class CreatedMailBox {
	public:
		CreatedMailBox(std::string const & fileNameConfig);
		std::vector<MailBox> getMailBoxes();
	private:
		std::string fileNameConfig_;
		MailBox makeMailBox_(TiXmlElement* mailBoxXML);
};
