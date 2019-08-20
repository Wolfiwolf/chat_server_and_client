#pragma once

#include "InternetIncludes.hpp"

class Client
{
private:
    std::string m_name;
    int m_socket;

    bool m_in_chat;

public:
    Client();
    Client(const std::string& name, int socket);


    inline const std::string& get_name() const
    {
        return m_name;
    }

    inline const int& get_socket() const
    {
        return m_socket;
    }

    inline  bool is_in_chat() const
    {
        return m_in_chat;
    }

    inline void set_socket(int socket)
    {
        m_socket = socket;
    }

    inline void set_name(const std::string& name)
    {
        m_name = name;
    }

    inline void set_is_in_chat(bool is_in_chat)
    {
        m_in_chat = is_in_chat;
    }

};
