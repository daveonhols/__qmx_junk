
#include "Connections.hpp"

class OwnedQInstance {

public:
    OwnedQInstance(Connections& conns) : _conns(conns), _conn(conns.Take()) {}
    QInstance& getInstance() { return _conn; };
    ~OwnedQInstance() { _conns.Return(std::move(_conn)); };

private: 
    QInstance _conn;
    Connections& _conns;
};