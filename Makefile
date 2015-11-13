glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=-lvmime

all: myprog

myprog: MailBox.o Message.o NotifyMessage.o certificateVerifier.o MailBoxSetting.o messagesmodule.c CreatedMailBoxes.o
	g++ -std=c++11 -shared -fPIC -I/usr/include/python2.7/ -lpython2.7 messagesmodule.c MailBox.o Message.o NotifyMessage.o  certificateVerifier.o MailBoxSetting.o CreatedMailBoxes.o -ltinyxml $(vmime) $(notify)-o messagesmodule.so
MailBox.o: MailBox.cpp
	g++ -std=c++11 -c -fPIC MailBox.cpp
Message.o: Message.cpp
	g++ -std=c++11 -c -fPIC Message.cpp
NotifyMessage.o: NotifyMessage.cpp
	g++ -std=c++11 -c -fPIC $(glib) $(gdk) NotifyMessage.cpp
certificateVerifier.o: certificateVerifier.cpp
	g++ -std=c++11 -c -fPIC certificateVerifier.cpp
CreatedMailBoxes.o: MailBox.hpp CreatedMailBoxes.cpp CreatedMailBoxes.hpp MailBoxSetting.hpp
	g++ -std=c++11 -c -fPIC CreatedMailBoxes.cpp
MailBoxSetting.o: MailBoxSetting.cpp
	g++ -std=c++11 -c -fPIC MailBoxSetting.cpp

clean:
	rm -rf *.o *.so myprog
