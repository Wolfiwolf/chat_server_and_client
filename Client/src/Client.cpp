#include "Client.hpp"

int Client::m_socket;

void Client::connect_to_server(const std::string& ip_adress)
{

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1)
    {
        return;
    }


    int port = 50132;
    std::string ipAddress = ip_adress;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


    int connectRes = connect(m_socket, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return;
    }


}

std::string Client::receive_from_server()
{
    std::string msg;

    char buffer[4096];

    memset(buffer, 0, 4096);
    int bytesReceived = recv(m_socket, buffer, 4096, 0);
    if (bytesReceived == -1)
    {
        std::cout << "There was an error getting response from server\n";
        return "ERROR";
    }
    else if (bytesReceived == 0)
    {
        return "ERROR";
    }
    else
    {
        msg = std::string(buffer, bytesReceived);
    }

    return msg;
}

void Client::send_to_server(const std::string& msg)
{
    int sendRes = send(m_socket, msg.c_str(), msg.size() + 1, 0);
    if (sendRes == -1)
    {
        std::cout << "Could not send to server! Whoops!\r\n";
    }
}

void Client::cleanup()
{
    close(m_socket);
}
