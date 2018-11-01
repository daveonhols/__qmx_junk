#ifndef ASLH_H
#define ASLH_H

#include <vector>
#include <future>

#include "ILoginHandler.hpp"
#include "Connections.hpp"

class AsyncLoginHandler : public ILoginHandler {
    public:
        AsyncLoginHandler(Connections& conns) : _conns(conns), _pending() {}
        void onLogin(int fd);
    private:
        Connections& _conns;
        std::vector<std::future<void>> _pending;
};

#endif