#include "ISocket.hpp"


#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

class ILoginHandler {
    public:
        virtual void onLogin(int fd) = 0;
};

#endif