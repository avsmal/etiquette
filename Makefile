glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=`pkg-config --cflags --libs vmime`

all: myprog

myprog: main.o MailBox.o Message.o NotifyMessage.o MailBoxSetting.o certificateVerifier.o
	g++ -std=c++11 main.o MailBox.o Message.o NotifyMessage.o MailBoxSetting.o certificateVerifier.o $(vmime) $(notify)-o myprog
main.o: main.cpp MailBox.hpp Message.hpp NotifyMessage.hpp MailBoxSetting.hpp
	g++ -std=c++11 -c main.cpp
MailBox.o: MailBox.cpp Message.hpp MailBoxSetting.hpp MailBox.hpp timeoutHandler.hpp
	g++ -std=c++11 -c MailBox.cpp
Message.o: Message.cpp Message.hpp
	g++ -std=c++11 -c Message.cpp
NotifyMessage.o: NotifyMessage.cpp NotifyMessage.hpp Message.hpp
	g++ -std=c++11 -c $(glib) $(gdk) NotifyMessage.cpp
MailBoxSetting.o: MailBoxSetting.cpp MailBoxSetting.hpp
	g++ -std=c++11 -c MailBoxSetting.cpp
certificateVerifier.o: certificateVerifier.cpp certificateVerifier.hpp
	g++ -std=c++11 -c certificateVerifier.cpp
clean:
	rm -rf *.o myprog
