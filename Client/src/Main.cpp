#include <iostream>
#include <thread>

#include "Client.hpp"


void listen_to_server(bool& running)
{
    std::string msg;
    while(running)
    {
        msg = Client::receive_from_server();

        std::cout << "\r\n" << msg << "\n";
        std::cout.flush();
    }
}

int main()
{
    std::cout << "If you are running the server on the same computer type 127.0.0.1\n\n";

    std::cout << "Server ip: ";
    std::string ip_address;
    std::cin >> ip_address;


    Client::connect_to_server(ip_address);


    std::cout << Client::receive_from_server() << "\n";


    std::string msg;

    std::cin >> msg;

    Client::send_to_server(msg);

    bool running = true;

    std::thread listener(listen_to_server, std::ref(running));
    listener.detach();

    while(running)
    {
        getline(std::cin, msg);


        Client::send_to_server(msg);


        if(msg == "EXIT")
            running = false;

    }



    return 0;
}
