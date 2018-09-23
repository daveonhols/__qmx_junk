#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

class LoginHandler {
    public:
        virtual void onLogin(int fd) = 0;
};

#endif