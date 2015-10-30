all:
	g++ main.cpp MailBox.cpp Message.cpp NotifyMessage.cpp -std=c++11 -o myprog -lvmime `pkg-config --cflags glib-2.0` `pkg-config --cflags gdk-pixbuf-2.0` `pkg-config --cflags --libs libnotify`
