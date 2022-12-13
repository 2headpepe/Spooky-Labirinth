#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class ClientNetwork {
    sf::Packet last_packet;

    bool isConnected = false;
public:
    sf::TcpSocket socket;

    ClientNetwork();
    void Connect(const char*, unsigned short);
    std::pair<std::string,std::string> ReceivePackets(sf::TcpSocket*, std::string& );
    void SendPacket(sf::Packet&);
    void Run();
};