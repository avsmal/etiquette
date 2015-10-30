#include "NotifyMessage.hpp"
#include "Message.hpp"
#include <string>
#include <libnotify/notify.h>
#include <stdio.h>
#include <unistd.h>


NotifyMessage::NotifyMessage(Message msg):
	msg_(msg)
	{}


void NotifyMessage::printNotify(void) {
	//Notify::init("New Message");
	//Notify::Notification Hello("New Message", "You do not answer message:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject(), "dialog-information");
	//Hello.show();
	//("You do not answer message:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject()).c_str()

	notify_init ("New Message");
	NotifyNotification * Hello = notify_notification_new ("New Message", ("You do not answer message:" + msg_.getFrom() + "\nSubject:" + msg_.getSubject()).c_str(), "dialog-information");
	notify_notification_show (Hello, NULL);
	g_object_unref(G_OBJECT(Hello));
	notify_uninit();
}



