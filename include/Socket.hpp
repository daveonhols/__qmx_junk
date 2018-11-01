#include <ISocket.hpp>

class Socket : public ISocket {
    public:
        Socket(int fd) : _fd(fd) {};
        Socket(std::string host, int port);
        ~Socket() override;
        std::vector<unsigned char> ReadFully() override;
        std::vector<unsigned char> ReadChunk() override;
        void Write(std::vector<unsigned char>) override;        
        void ForwardRemaining(std::vector<unsigned char> initial, ISocket& to) override;
        void ForwardAll(ISocket& to) override;
        Socket(Socket&& other) : _fd(other._fd) { other._fd = 0; };
        Socket& operator=(Socket&& other) = delete;
    private:
        long getQueryLength(std::vector<unsigned char> header);
        const int CHUNK_SIZE = 1024;
        int _fd;
};
