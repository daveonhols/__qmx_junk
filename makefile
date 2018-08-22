
server: server.o SimpleSocket.o Connections.o 
	g++ -std=c++14 -o server server.o SimpleSocket.o Connections.o -lpthread

server.o: server.cpp Job.hpp Task.hpp Connections.hpp
	g++ -std=c++14 -Wall -c server.cpp 

SimpleSocket.o: SimpleSocket.cpp SimpleSocket.hpp
	g++ -std=c++14 -Wall -c SimpleSocket.cpp 

Connections.o: Connections.cpp Connections.hpp
	g++ -std=c++14 -Wall -c Connections.cpp 




#ByteReader.o: ByteReader.hpp
#	g++ -std=c++14 -Wall -c ByteReader.hpp

clean:
	rm *.o server

# g++ -std=c++14 server.cpp SimpleSocket.cpp Connections.cpp -Wall -lpthread -o server
