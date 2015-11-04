#include <string>
#include <libnotify/notify.h>
#include <stdio.h>
#include <unistd.h>

#include "NotifyMessage.hpp"
#include "Message.hpp"

NotifyMessage::NotifyMessage(Message const & msg):
	msg_(msg)
	{}


void NotifyMessage::printNotify(void) {
	//Notify::init("New Message");
	//Notify::Notification Hello("New Message", "You do not answer message:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject(), "dialog-information");
	//Hello.show();
	//("You do not answer message:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject()).c_str()

	notify_init ("New Message");
	NotifyNotification * newMessage = notify_notification_new ("New Message", ("You do not answer message:\nEmail:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject()).c_str(), "dialog-information");
	notify_notification_show (newMessage, NULL);
	g_object_unref(G_OBJECT(newMessage));
	notify_uninit();
}



