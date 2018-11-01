#include "IListenServer.hpp"
#include "ILoginHandler.hpp"

class QMXListenServer : public IListenServer {
    public:
        void Listen();
        QMXListenServer(int port, ILoginHandler& login);
        ~QMXListenServer();
    private:
        int _fd;
        ILoginHandler& _login;
};