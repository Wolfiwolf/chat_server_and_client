#include <iostream>
#include <thread>
#include <termios.h>
#include "Server.hpp"



void listen_to_client(Client* client, bool& running)
{
    Server::send_to_client(client, "Enter your nickname: ");


    client->set_name(Server::receive_from(client));

    std::cout << client->get_name() << " entered the chat!\n";
    Server::send_to_client(client, client->get_name() + " you have entered the chat!\n");
    Server::send_to_clients(client, client->get_name() + " has joined the chat!\n");



    client->set_is_in_chat(true);

    Server::receive_from(client);

    std::string msg = "";
    while(running)
    {

        msg = Server::receive_from(client);

        if(msg.find("EXIT") != std::string::npos)
        {
            std::cout << client->get_name() << " exited the chat!\n";
            Server::send_to_client(client, client->get_name() + " you exited the chat!\n");
			Server::send_to_clients(client, client->get_name() + " exited the chat!\n");
            break;
        }

        msg = client->get_name() + "> " + msg;
        Server::send_to_clients(client, msg);

        std::cout << msg << "\n";
    }
}

void listen_for_clients(bool& running)
{

    while(running)
    {
        Client* client = new Client();

        client->set_socket(Server::wait_for_connection());

        Server::add_client(client);

        std::thread worker(listen_to_client, client, std::ref(running));
        worker.detach();

    }
}



int main()
{
    printf("%s\n", "SERVER HAS STARTED");


    Server::init();

    bool running = true;

    std::thread worker(listen_for_clients, std::ref(running));

    worker.detach();

    while(getchar() != 'X');

    running = false;

    return 0;
}
