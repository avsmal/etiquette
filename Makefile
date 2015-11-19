glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=`pkg-config --cflags --libs vmime`
python=-I/usr/include/python2.7/ -lpython2.7
tinyxml=-ltinyxml


all: bin/messagesmodule.so

bin/messagesmodule.so: bin/messagesmodule.o bin/MailBoxSetting.o bin/certificateVerifier.o bin/NotifyMessage.o bin/Message.o bin/MailBox.o bin/CreatedMailBoxes.o
	g++ -std=c++11 -shared bin/messagesmodule.o bin/MailBox.o bin/Message.o bin/NotifyMessage.o bin/certificateVerifier.o bin/MailBoxSetting.o bin/CreatedMailBoxes.o $(tinyxml) $(python) $(vmime) $(notify) -o $@

bin/MailBox.o: src/net/MailBox.cpp src/net/timeoutHandler.hpp src/net/Message.hpp src/net/MailBoxSetting.hpp src/net/certificateVerifier.hpp
	g++ -std=c++11 -c -fPIC src/net/MailBox.cpp -o $@

bin/Message.o: src/net/Message.cpp src/net/Message.hpp
	g++ -std=c++11 -c -fPIC src/net/Message.cpp -o $@

bin/NotifyMessage.o: src/net/Message.hpp src/ui/cpp/NotifyMessage.cpp src/ui/cpp/NotifyMessage.hpp
	g++ -std=c++11 -c -fPIC $(glib) $(gdk) src/ui/cpp/NotifyMessage.cpp -o $@

bin/certificateVerifier.o: src/net/certificateVerifier.cpp src/net/certificateVerifier.hpp
	g++ -std=c++11 -c -fPIC src/net/certificateVerifier.cpp -o $@

bin/CreatedMailBoxes.o: src/net/MailBox.hpp src/net/CreatedMailBoxes.cpp src/net/CreatedMailBoxes.hpp src/net/MailBoxSetting.hpp
	g++ -std=c++11 -c -fPIC src/net/CreatedMailBoxes.cpp -o $@

bin/MailBoxSetting.o: src/net/MailBoxSetting.cpp src/net/MailBoxSetting.hpp
	g++ -std=c++11 -c -fPIC src/net/MailBoxSetting.cpp -o $@

bin/messagesmodule.o: src/net/messagesmodule.c src/ui/cpp/NotifyMessage.hpp src/net/Message.hpp
	g++ -std=c++11 -c -fPIC $(python) src/net/messagesmodule.c -o $@

clean:
	rm -rf bin/*.o bin/*.so
