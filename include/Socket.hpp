#include <ISocket.hpp>

class Socket : public ISocket {
    public:
        Socket(int fd) : ISocket(fd) {};
        Socket(std::string host, int port) : ISocket(host, port) {};
        std::vector<char> Read() override;
        std::vector<char> ReadChunk() override;
        void Write(std::vector<char>) override;
        void Show() override {std::cout << "Derived(" << _fd << ")" << std::endl;}
        Socket(Socket&& other) : ISocket(other._fd) { other._fd = 0; std::cout << "[[Socket()]]" << std::endl; };
        Socket& operator=(Socket&& other) = delete;
};
