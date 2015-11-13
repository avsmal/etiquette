glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=`pkg-config --cflags --libs vmime`
python=-I/usr/include/python2.7/ -lpython2.7
tinyxml=-ltinyxml

all: myprog

myprog: messagesmodule.o MailBox.o Message.o NotifyMessage.o certificateVerifier.o MailBoxSetting.o CreatedMailBoxes.o
	g++ -std=c++11 -shared messagesmodule.o MailBox.o Message.o NotifyMessage.o certificateVerifier.o MailBoxSetting.o CreatedMailBoxes.o $(tinyxml) $(python) $(vmime) $(notify)-o messagesmodule.so

MailBox.o: MailBox.cpp timeoutHandler.hpp Message.hpp MailBoxSetting.hpp certificateVerifier.hpp
	g++ -std=c++11 -c -fPIC MailBox.cpp

Message.o: Message.cpp Message.hpp
	g++ -std=c++11 -c -fPIC Message.cpp

NotifyMessage.o: NotifyMessage.cpp Message.hpp NotifyMessage.hpp
	g++ -std=c++11 -c -fPIC $(glib) $(gdk) NotifyMessage.cpp

certificateVerifier.o: certificateVerifier.cpp certificateVerifier.hpp
	g++ -std=c++11 -c -fPIC certificateVerifier.cpp

CreatedMailBoxes.o: MailBox.hpp CreatedMailBoxes.cpp CreatedMailBoxes.hpp MailBoxSetting.hpp
	g++ -std=c++11 -c -fPIC CreatedMailBoxes.cpp

MailBoxSetting.o: MailBoxSetting.cpp MailBoxSetting.hpp
	g++ -std=c++11 -c -fPIC MailBoxSetting.cpp

messagesmodule.o: messagesmodule.c
	g++ -std=c++11 -c -fPIC $(python) messagesmodule.c

clean:
	rm -rf *.o *.so myprog
