#include <Python.h>

#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>


#include "MailBox.hpp"
#include "Message.hpp"
#include "../ui/cpp/NotifyMessage.hpp"
#include "CreatedMailBoxes.hpp"

static PyObject* py_getmessages(PyObject* self, PyObject* args)
{
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();

	std::string config = "config.xml";
	CreatedMailBox createdMailBox(config);
	std::vector<MailBox> mailBoxes = createdMailBox.getMailBoxes();
	PyObject * ans = NULL;
	for (size_t i = 0; i < mailBoxes.size(); ++i)
	{
		mailBoxes[i].connect();
		std::vector<Message> messages = mailBoxes[i].getUnAnswered();
		PyObject * res = PyList_New(messages.size());
		for(size_t i = 0; i < messages.size(); ++i)
		{
			Message msg = messages[i];
			NotifyMessage notifyMessage(msg);
			notifyMessage.printNotify();
			PyList_SetItem(res, i, PyString_FromString(messages[i].getFrom().c_str()));
		}
		ans = res;
	}
	return ans;
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
