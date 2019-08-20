#include "Server.hpp"


int Server::m_listening_socket;
sockaddr_in Server::m_hint;
std::vector<Client*>  Server::m_clients;


bool Server::init()
{
    m_listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_listening_socket == -1)
    {
        std::cout << "Can't create a socket!\n";
        return false;
    }

    m_hint.sin_family = AF_INET;
    m_hint.sin_port = htons(50132);
    inet_pton(AF_INET, "0.0.0.0", &m_hint.sin_addr);

    bind(m_listening_socket, (sockaddr*)&m_hint, sizeof(m_hint));

    listen(m_listening_socket, SOMAXCONN);



    return true;
}

int Server::wait_for_connection()
{
    sockaddr_in client_info;
    socklen_t clientSize = sizeof(client_info);

    int client_socket = accept(m_listening_socket, (sockaddr*)&client_info, &clientSize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client_info, sizeof(client_info), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << host << " connected on port " << service << "\n";
    }
    else
    {
        inet_ntop(AF_INET, &client_info.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client_info.sin_port) << "\n";
    }

    return client_socket;

}

std::string Server::receive_from(const Client* client)
{
    char* buffer = new char[4096];
    memset(buffer, 0, 4096);

    int bytesReceived = recv(client->get_socket(), buffer, 4096, 0);
    if (bytesReceived == -1)
    {
        std::cout << "Receiving failed!\n";
        return "";
    }
    if (bytesReceived == 0)
    {
        std::cout << "Client disconnected!\n";
        return "EXIT";
    }

    std::string msg = std::string(buffer, 0, bytesReceived);

    delete[] buffer;

    return msg;
}

void Server::send_to_clients(const Client* sender_client, const std::string& msg)
{

    for(const Client* client : m_clients)
    {
        if(client == sender_client || !client->is_in_chat())
            continue;

        send(client->get_socket(), msg.c_str(), msg.size() + 1, 0);

    }

}

void Server::send_to_client(const Client* client, const std::string& msg)
{

    send(client->get_socket(), msg.c_str(), msg.size() + 1, 0);

}

void Server::add_client(Client* client)
{
    m_clients.push_back(client);
}

void Server::cleanup()
{
    for(Client* client : m_clients)
    {
        close(client->get_socket());
        delete client;
    }

    close(m_listening_socket);
}
