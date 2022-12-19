#include "clientnetwork.hpp"
#include "variables.h"
#include "player.h"
#include "shooter2.h"

ClientNetwork::ClientNetwork()
{
    logl("Chat Client Started");
}

void ClientNetwork::Connect(const char* address, unsigned short port)
{
    if (socket.connect(address, port) != sf::Socket::Done)
    {
        logl("Could not connect to the server\n");
    }
    else
    {
        isConnected = true;
        logl("Connected to the server\n");
    }
}


//std::map <std::string, std::string> users;
//std::vector<std::string> users;


//class Users {
//public:
//    static std::map < std::string, std::string>& get() {
//        return users;
//    }
//};

std::pair<std::string,std::string> ClientNetwork::ReceivePackets(sf::TcpSocket* socket, std::string &users)
{
    while (true)
    {
        if (socket->receive(last_packet) == sf::Socket::Done)
        {
            std::string received_string;
            std::string sender_address;
            unsigned short sender_port;
            last_packet >> received_string >> sender_address >> sender_port;
            //addUser(received_string);
            users+=received_string;
            //users["1"] = received_string;
            //logl("From (" << sender_address << ":" << sender_port << "): " << received_string);
        }

    //    std::this_thread::sleep_for((std::chrono::milliseconds)250);
    }
}

void ClientNetwork::SendPacket(sf::Packet& packet)
{
    if (packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done)
    {
        logl("Could not send packet");
    }
}

std::string usersOld = "";
rect userRect;

double x = 0.0;
double y = 0.0;


void ClientNetwork::Run()
{
    std::string users;
    std::thread reception_thred(&ClientNetwork::ReceivePackets, this, &socket,std::ref(users));
    //reception_thred.join();

   while (true)
    {
        if (isConnected)
        {
            sf::RenderWindow window(sf::VideoMode(worldSizeX, worldSizeY), "Source 2");
            player player1;
            rect* walls = new rect[countRays];
            
            std::vector<rect> boards(36);
            std::ifstream json("map.txt");
            if (!json.is_open()) {
                std::cout << 0;
            }
            map(window, boards, jsonGet(json));

            std::vector<rect> playersView;

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        player1.angle += 10;
                        player1.view.rectangle.rotate(-10);
                        player1.speedX = mapSizeX / 100 * cos(player1.angle * pi / 180);
                        player1.speedY = mapSizeX / 100 * sin(player1.angle * pi / 180);

                        /* player1.speedX = findSpeed(player1, boards).x;
                         player1.speedY = findSpeed(player1, boards).y;
                         player1.angle = atan(player1.speedY / player1.speedX)*180/pi;
                         std::cout << "hello";*/

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        player1.angle -= 10;
                        player1.view.rectangle.rotate(10);
                        player1.speedX = mapSizeX / 100 * cos(player1.angle * pi / 180);
                        player1.speedY = mapSizeX / 100 * sin(player1.angle * pi / 180);

                        /*player1.speedX = findSpeed(player1, boards).x;
                        player1.speedY = findSpeed(player1, boards).y;
                        player1.angle = atan(player1.speedY / player1.speedX)*180/pi;
                        std::cout << "hello";*/


                        /* for (int i = 0; i < countRays; i++)
                         {
                             int currentAngle = player1.angle - player1.viewAngle / 2 + player1.viewAngle / countRays * i;
                             int len = findNeighbour(player1.location, currentAngle, boards);
                             int lenx = len * cos(player1.viewAngle / countRays * i * pi / 180);
                             int leny = len * sin(player1.viewAngle / countRays * i * pi / 180);
                             if((lenx>0) &&(player1.speedX>0))
                                 if (lenx <= player1.speedX) player1.speedX = lenx;
                             if ((lenx < 0) && (player1.speedX < 0))
                                 if (lenx >= player1.speedX) player1.speedX = lenx;
                             if ((leny > 0) && (player1.speedY > 0))
                                 if (leny <= player1.speedY) player1.speedY = leny;
                             if ((leny < 0) && (player1.speedY < 0))
                                 if (leny >= player1.speedY) player1.speedY = leny;
                         }*/
                         //if (player1.weapons[player1.weaponNum].img.getPosition().y <= worldSizeY - player1.weapons[player1.weaponNum].sizeY) flag = 1;
                         //if (player1.weapons[player1.weaponNum].img.getPosition().y >= worldSizeY - player1.weapons[player1.weaponNum].sizeY + 50) flag = 0;

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        player1.location.y -= player1.speedY;
                        player1.location.x += player1.speedX;
                        player1.view.rectangle.setPosition(player1.location.x + player1.bodySize / 2, player1.location.y + player1.bodySize / 2);

                        std::string str = std::to_string(player1.location.x) + " " + std::to_string(player1.location.y);
                        sf::Packet packet;
                        packet << str;
                        SendPacket(packet);


                        //if (player1.weapons[player1.weaponNum].img.getPosition().y <= worldSizeY - player1.weapons[player1.weaponNum].sizeY) flag = 1;
                        //if (player1.weapons[player1.weaponNum].img.getPosition().y >= worldSizeY - player1.weapons[player1.weaponNum].sizeY + 30) flag = 0;

                        //if (flag)
                        //{
                        //    //weaponPosition.x += weapon;
                        //    player1.weapons[player1.weaponNum].weaponPosition.y += player1.weapons[player1.weaponNum].weaponSpeed;
                        //}
                        //else
                        //{
                        //    //weaponPosition.x -= 0.3;
                        //    player1.weapons[player1.weaponNum].weaponPosition.y -= player1.weapons[player1.weaponNum].weaponSpeed;
                        //}
                        //player1.weapons[player1.weaponNum].img.setPosition(player1.weapons[player1.weaponNum].weaponPosition);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        player1.location.y += player1.speedY;
                        player1.location.x -= player1.speedX;
                        player1.view.rectangle.setPosition(player1.location.x + player1.bodySize / 2, player1.location.y + player1.bodySize / 2);


                        std::string str = std::to_string(player1.location.x) + " " + std::to_string(player1.location.y);
                        sf::Packet packet;
                        packet << str;
                        SendPacket(packet);

                        //if (player1.weapons[player1.weaponNum].img.getPosition().y <= worldSizeY - player1.weapons[player1.weaponNum].sizeY) flag = 1;
                        //if (player1.weapons[player1.weaponNum].img.getPosition().y >= worldSizeY - player1.weapons[player1.weaponNum].sizeY + 30) flag = 0;

                        //if (flag)
                        //{
                        //    //weaponPosition.x += weapon;
                        //    player1.weapons[player1.weaponNum].weaponPosition.y += player1.weapons[player1.weaponNum].weaponSpeed;
                        //}
                        //else
                        //{
                        //    //weaponPosition.x -= 0.3;
                        //    player1.weapons[player1.weaponNum].weaponPosition.y -= player1.weapons[player1.weaponNum].weaponSpeed;
                        //}
                        //player1.weapons[player1.weaponNum].img.setPosition(player1.weapons[player1.weaponNum].weaponPosition);
                    }
                    player1.body.rectangle.setPosition(player1.location.x, player1.location.y);



                }
                window.clear();




                //Îòðèñîâêà ìèðà

                sf::RectangleShape backGround(sf::Vector2f(0, 0));
                backGround.setSize(sf::Vector2f(worldSizeX, worldSizeY / 2));
                backGround.setFillColor(sf::Color(16, 22, 24));
                window.draw(backGround);

                sf::RectangleShape floor;
                floor.setPosition(sf::Vector2f(0, worldSizeY / 2));
                floor.setSize(sf::Vector2f(worldSizeX, worldSizeY / 2));

                floor.setFillColor(sf::Color(12, 7, 7));
                window.draw(floor);

                double* distance = new double[countRays];
                double* userDistance = new double[countRays];
                bool* flag = new bool[countRays];
                for (int i = 0; i < countRays; ++i)
                {
                    distance[i] = findNeighbour(player1.location, player1.angle - player1.viewAngle / 2 + player1.viewAngle * i / countRays, boards);

                    userDistance[i] = findNeighbour(player1.location, player1.angle - player1.viewAngle / 2 + player1.viewAngle * i / countRays, userRect);
                    
/*double newDist = findNeighbour(player1.location, player1.angle - player1.viewAngle / 2 + player1.viewAngle * i / countRays, playersView);
                    if (distance[i] > newDist)
                    {
                        distance[i] = newDist;
                        flag[i] = 1;
                    }
                    else flag[i] = 0;*/
                }

                double coef = 5;
                coordinates wallsSize(10, worldSizeY / distance[0] * coef);
                coordinates wallsLocation(worldSizeX - 10, worldSizeY / 2 * (1 - coef / distance[0]));


                sf::Color wallsColor(255, 151, 187);
                bool userColor = 0;
                for (int i = 0; i < countRays; ++i)
                {
                    if (distance[i] > userDistance[i]) {
                        distance[i] = userDistance[i];
                        userColor = 1;
                    }

                    wallsLocation.y = worldSizeY / 2 - worldSizeY / 2 * coef / distance[i];
                    wallsSize.y = worldSizeY * coef / distance[i];
                    

                    double distCoef = pow(1.05, distance[i]);
                    //if (distance[i] >= 100) distCoef = pow(1.05, 100);

                    //if(!flag[i])

                    if (player1.location.x > passageSize * 3) {

                    }

                    if (player1.location.x > passageSize * 3) {

                    }


                    if (userColor) walls[i].rectangle.setFillColor(sf::Color(0, 0, 255));
                    else
                    walls[i].rectangle.setFillColor(sf::Color(wallsColor.r / distCoef, wallsColor.g / distCoef, wallsColor.b / distCoef));
                    //else 
                    //    walls[i].rectangle.setFillColor(sf::Color(0,0,0));
                    userColor = false;
                    walls[i].setCharacteristics(wallsLocation.x, wallsLocation.y, wallsSize.x, wallsSize.y);
                    window.draw(walls[i].rectangle);

                    wallsLocation.x -= wallsSize.x;



                }                    
               /* if(users!="")
                    logl(users);*/




                //for (auto player : users) {
                




                //window.draw(player1.view.rectangle);

                //Îòðèñîâêà ìèíè-êàðòû
               /*sf::RectangleShape mapBackGround;
                mapBackGround.setSize(sf::Vector2f(passageSize*9, passageSize * 7));
                mapBackGround.setFillColor(sf::Color(3, 3, 20));
                window.draw(mapBackGround);*/

                //player1.view.rectangle.rotate(player1.viewAngle / 2);

                /*for (int i = 0; i < countRays; i++)
                {

                    int len = findNeighbour(player1.location, player1.angle - player1.viewAngle / 2 + player1.viewAngle / countRays * i, boards);
                    player1.view.rectangle.setSize(sf::Vector2f(len, 1));
                    window.draw(player1.view.rectangle);
                    player1.view.rectangle.rotate(-player1.viewAngle / countRays);
                }
                player1.view.rectangle.rotate(player1.viewAngle / 2);*/

                //player1.view.rectangle.setFillColor(sf::Color(0, 0, 0, 0));
                //window.draw(player1.view.rectangle);

                //weapon



                //window.draw(player1.weapons[0].img);



                /*for (int i = 0; i < boards.size(); ++i)
                {
                    boards[i].rectangle.setFillColor(wallsColor);
                    window.draw(boards[i].rectangle);
                }
                window.draw(player1.body.rectangle);*/
                

                if (users != "") {
                    int i = 0;
                    bool flag = 0;
                    std::string tmp = "";
                    while (users[i] != ' ') {
                        tmp += users[i];
                        ++i;
                    }
                    x = stod(tmp);
                    tmp = "";
                    ++i;
                    while (i < users.length()) {
                        tmp += users[i];
                        ++i;
                    }
                    y = stod(tmp);

                    logl(x << y);

                    userRect.setCharacteristics(x,y,3,3);
                    userRect.rectangle.setFillColor(sf::Color(0, 0, 255));
                    userRect.rectangle.setSize(sf::Vector2f(3, 3));
                    window.draw(userRect.rectangle);
                }
                else if ((x != 0.0) && (y != 0)) {
                    userRect.setCharacteristics(x, y, 3, 3);
                    userRect.rectangle.setFillColor(sf::Color(0, 0, 255));
                    userRect.rectangle.setSize(sf::Vector2f(3, 3));
                    window.draw(userRect.rectangle);
                }
                


                users.clear();

                window.display();
            }


            /*std::string user_input;
            std::getline(std::cin, user_input);

            if (user_input.length() < 1)
                continue;

            sf::Packet reply_packet;
            reply_packet << user_input;

            SendPacket(reply_packet);*/
        }
    }
}
