#pragma once

#include <vector>

#include "InternetIncludes.hpp"

#include "Client.hpp"

class Server
{
private:
    static int m_listening_socket;
    static sockaddr_in m_hint;

    static std::vector<Client*> m_clients;
public:

    static bool init();
    static void cleanup();
    static int wait_for_connection();
    static std::string receive_from(const Client* client);
    static void send_to_clients(const Client* sender_client, const std::string& msg);
    static void send_to_client(const Client* client, const std::string& msg);
    static void add_client(Client* client);

};
