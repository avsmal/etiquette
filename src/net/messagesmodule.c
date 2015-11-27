#include <Python.h>

#include <iostream>
#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>


#include "MailBox.hpp"
#include "Message.hpp"
#include "../ui/cpp/NotifyMessage.hpp"
#include "Accounts.hpp"
#include "Setting.hpp"

static PyObject* py_getmessages(PyObject* self, PyObject* args) {
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
	Setting s("config.xml");
	Accounts acc(s);
    std::map <std::string, std::vector<Message>> map = acc.getUnAnswered();

    PyObject * ans = PyList_New(map.size());
    int k = 0;
    for (auto itMap = map.begin(); itMap != map.end(); ++itMap) {
         std::vector<Message> messages = itMap->second;
         PyObject * res = PyList_New(messages.size());

        for (size_t i = 0; i < messages.size(); ++i) {
			Message msg = messages[i];
			PyList_SetItem(res, i, PyString_FromString(messages[i].getFrom().c_str()));
		}
        PyObject * entry = PyList_New(2);
		PyList_SetItem(entry, 0, PyString_FromString(itMap->first.c_str()));
        PyList_SetItem(entry, 1, res);
        PyList_SetItem(ans, k, entry);
        ++k;
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
