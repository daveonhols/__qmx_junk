class SimpleSocket
{
private:
  int sockfd;
public:
  SimpleSocket(int port);
  ~SimpleSocket();
  int waitForConnection();
};
