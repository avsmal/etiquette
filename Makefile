glib=`pkg-config --cflags glib-2.0`
gdk=`pkg-config --cflags gdk-pixbuf-2.0`
notify=`pkg-config --cflags --libs libnotify`
vmime=`pkg-config --cflags --libs vmime`
python=-I/usr/include/python2.7/ -lpython2.7
tinyxml=-ltinyxml
LIB_TEST=-lgtest -lpthread -I /usr/gtest/include -lgtest_main

all: bin/messagesmodule.so bin/applet.py bin/config.xml

test: bin/test

bin/messagesmodule.so: bin/messagesmodule.o bin/MailBoxSetting.o bin/certificateVerifier.o bin/NotifyMessage.o bin/Message.o bin/MailBox.o bin/CreatedMailBoxes.o bin/Setting.o bin/Accounts.o
	g++ -std=c++11 -shared bin/messagesmodule.o bin/MailBox.o bin/Message.o bin/NotifyMessage.o bin/certificateVerifier.o bin/MailBoxSetting.o bin/CreatedMailBoxes.o bin/Accounts.o bin/Setting.o $(tinyxml) $(python) $(vmime) $(notify) -o $@

bin/test: bin/messagesmodule.o bin/MailBoxSetting.o bin/certificateVerifier.o bin/NotifyMessage.o bin/Message.o bin/MailBox.o bin/CreatedMailBoxes.o bin/Setting.o bin/Accounts.o bin/test.o
	g++ -std=c++11 bin/messagesmodule.o bin/MailBox.o bin/Message.o bin/NotifyMessage.o bin/certificateVerifier.o bin/MailBoxSetting.o bin/CreatedMailBoxes.o bin/Accounts.o bin/Setting.o bin/test.o $(tinyxml) $(python) $(vmime) $(notify) $(LIB_TEST) -o $@

bin/test.o: test/test.cpp src/net/MailBox.hpp src/net/MailBoxSetting.hpp
	g++ -std=c++11 -c $(LIB_TEST) test/test.cpp -o $@
bin/Accounts.o: src/net/Accounts.hpp src/net/Accounts.cpp src/net/Setting.hpp
	g++ -std=c++11 -c -fPIC src/net/Accounts.cpp -o $@

bin/Setting.o: src/net/Setting.hpp src/net/Setting.cpp
	g++ -std=c++11 -c -fPIC src/net/Setting.cpp -o $@

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

bin/applet.py: src/ui/py/applet.py
	cp ./src/ui/py/applet.py bin/

bin/config.xml: config.xml
	cp ./config.xml bin/


clean:
	rm -rf bin/*.o bin/*.so bin/*.py bin/*.xml
