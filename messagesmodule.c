#include <Python.h>

#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>


#include "MailBox.hpp"
#include "Message.hpp"
#include "NotifyMessage.hpp"
#include "MailBoxSetting.hpp"

static PyObject* py_getmessages(PyObject* self, PyObject* args)
{
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
	std::string login;
	std::string password;
	std::string server;
	
	login =  "test.imap2015@mail.ru";
	password = "824222443a";
	server =  "imap.mail.ru:993";

	std::vector<std::string> ignoredMailBox;
	ignoredMailBox.push_back("Spam");
	ignoredMailBox.push_back("Trash");
	ignoredMailBox.push_back("Sent");

	MailBoxSetting mailBoxSetting(ignoredMailBox);


	MailBox mailbox(login, password, server, mailBoxSetting);
	mailbox.connect();
	std::vector<Message> messages = mailbox.getUnAnswered();
	PyObject * res = PyList_New(messages.size());
	for(size_t i = 0; i < messages.size(); ++i)
	{
		Message msg = messages[i];
		NotifyMessage notifyMessage(msg);
		notifyMessage.printNotify();
		PyList_SetItem(res, i, PyString_FromString(messages[i].getFrom().c_str()));
	}
	return res;
}

static PyMethodDef myModule_methods[] = {
  {"getMessages", py_getmessages, METH_VARARGS},
  {NULL, NULL}
};

extern "C"{

void initmessagesmodule()
{
  (void) Py_InitModule("messagesmodule", myModule_methods);
}
}
