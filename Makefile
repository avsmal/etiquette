glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=-lvmime

all: myprog

myprog: main.o MailBox.o Message.o NotifyMessage.o certificateVerifier.o MailBoxSetting.o
	g++ -std=c++11 main.o MailBox.o Message.o NotifyMessage.o certificateVerifier.o MailBoxSetting.o $(vmime) $(notify)-o myprog
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
MailBox.o: MailBox.cpp
	g++ -std=c++11 -c MailBox.cpp
Message.o: Message.cpp
	g++ -std=c++11 -c Message.cpp
NotifyMessage.o: NotifyMessage.cpp
	g++ -std=c++11 -c $(glib) $(gdk) NotifyMessage.cpp
certificateVerifier.o: certificateVerifier.cpp
	g++ -std=c++11 -c certificateVerifier.cpp
MailBoxSetting.o: MailBoxSetting.cpp
	g++ -std=c++11 -c MailBoxSetting.cpp

clean:
	rm -rf *.o myprog

-std=c++11 -o myprog -lvmime 
