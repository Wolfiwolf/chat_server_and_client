#include "Client.hpp"

Client::Client()
    : m_name("empty")
    , m_socket(-1)
    , m_in_chat(false)
{

}

Client::Client(const std::string& name, int socket)
    : m_name(name)
    , m_socket(socket)
    , m_in_chat(false)
{

}
