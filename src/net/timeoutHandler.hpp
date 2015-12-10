#include <string>
#include <iostream>

/** Time out handler.
  * Used to stop the current operation after too much time, or if the user
  * requested cancellation.
  */
class timeoutHandler : public vmime::net::timeoutHandler {
public:

    bool isTimeOut() {
        return (getTime() >= last_ + 5);
    }

    void resetTimeOut() {
        last_ = getTime();
    }

    bool handleTimeOut() {
        return false;
    }
private:
    const unsigned int getTime() const {
        return vmime::platform::getHandler()->getUnixTime();
    }
    unsigned int last_;
};


class timeoutHandlerFactory : public vmime::net::timeoutHandlerFactory {
public:
    vmime::ref <vmime::net::timeoutHandler> create() {
        return vmime::create <timeoutHandler>();
    }
};

