#pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

class Client
{
private:
    static int m_socket;

public:
    static void connect_to_server(const std::string& ip_adress);
    static std::string receive_from_server();
    static void send_to_server(const std::string& msg);

    static void cleanup();
};
