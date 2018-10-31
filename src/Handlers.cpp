#include<vector>

#include "Handlers.hpp"
#include "OwnedQInstance.hpp"


void handleJob(ISocket&& socket, Connections &conns) {
  std::cout << "HHHH::" << std::endl;
  socket.Show();
  std::cout << "Job::" << std::endl;
  //char buffer[1];
  //buffer[0] = 3;
  std::vector<char> buffer;
  std::cout << "AAA::" << std::endl;
  buffer.push_back(3);
  std::cout << "BBB::" << std::endl;
  socket.Write(buffer);
  std::cout << "CCC::" << std::endl;
  std::cout << "Job done" << std::endl;

  while (true) {
    auto chars = socket.Read();
    //auto chars = getBytesFromQuery(job->_socket);

    if (0 == chars.size()) {
      std::cerr << "going away" << std::endl;
      break;
    }

    OwnedQInstance conn(conns);
    conn.getSocket().Write(chars);
    //conn.getInstance().AcceptBytes(chars);
    //forwardBytes(conn.getInstance().fd(), job->_fd);
    socketForwardBytes(conn.getSocket(), socket);
  }
  std::cerr << "Exiting" << std::endl;
}