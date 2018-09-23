#include "ListenServer.hpp"
#include "LoginHandler.hpp"

class QMXListenServer : public ListenServer {
    public:
        void Listen();
        QMXListenServer(int port, LoginHandler& login );
        ~QMXListenServer();
    private:
        int _fd;
        LoginHandler& _login;
};