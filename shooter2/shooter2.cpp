#include <SFML/Graphics.hpp>
#include<vector>
#include"objects.h"
#include<iostream>
#include"player.h"
#include"variables.h"

#include<SFML/Network.hpp>
#include<string>
#include<Windows.h>

int passageSize = 30;
int mapSizeX = 200;
int mapSizeY = 200;
int worldSizeX = mapSizeX * 5;
int worldSizeY = mapSizeX * 3;
int boardSize = mapSizeX / 50;
double pi = 4 * atan(1);
int countRays = 100;

//Player player(true);
#include "clientnetwork.hpp"
#include "servernetwork.hpp"
#include "shooter2.h"

int main()
{
    std::string type;
    std::cin >> type;
    if (type == "client")
    {
        ClientNetwork client_network;
        client_network.Connect("localHost", 2525);
        client_network.Run();
    }   
    else if(type =="server") {
        ServerNetwork server_network(2525);
        server_network.Run();
    }
    




    
    
    return 0;    
}

void map(const sf::RenderWindow& window, std::vector<rect>& boards)
{

    /*std::ifstream mapJson("map.json", std::ifstream::binary);
    std::string json;
    mapJson >> json;
    std::cout << json;
    logl(json);

    for (auto jsonx : json)
    {
        std::cout << jsonx["x"] << jsonx["y"];
    }*/


    // ГРАНИЦА КАРТЫ
    boards[0].setCharacteristics(0, 0, passageSize*9, 1);
    //boards[0].setCharacteristics(boardSize, boardSize, mapSizeX - boardSize * 2 - passageSize / 2, boardSize);
    boards[1].setCharacteristics(passageSize*9, 0, 1, passageSize*3);
    //boards[1].setCharacteristics(mapSizeX - boardSize * 2, boardSize, boardSize, mapSizeY / 2 + boardSize * 2 - passageSize / 2);
    boards[2].setCharacteristics(0, passageSize*7, passageSize*9, 1);
    //boards[2].setCharacteristics(boardSize, mapSizeX - boardSize * 2, mapSizeX - boardSize * 2, boardSize);
    boards[3].setCharacteristics(0, 0, 1, passageSize*3);
    //boards[3].setCharacteristics(boardSize, boardSize, boardSize, mapSizeY / 2 - boardSize * 2 - passageSize / 2);
    boards[4].setCharacteristics(0, passageSize*4, 1, passageSize*3);
    //boards[4].setCharacteristics(boardSize, mapSizeY / 2 - boardSize * 2 + passageSize / 2, boardSize, mapSizeY / 2 + boardSize * 2 - passageSize / 2);
    boards[5].setCharacteristics(passageSize*9, passageSize*4, 1,passageSize*3);
    //boards[5].setCharacteristics(mapSizeX - boardSize * 2, mapSizeY / 2 + passageSize / 2, boardSize, mapSizeY / 2 - boardSize * 2 - passageSize / 2);
    boards[6].setCharacteristics(0, passageSize *4, passageSize, 1);
    //boards[6].setCharacteristics(boardSize, mapSizeY / 2 - boardSize / 2 + passageSize / 2, passageSize, boardSize);
    boards[7].setCharacteristics(0, passageSize *3, passageSize, 1);
    boards[8].setCharacteristics(passageSize, passageSize, 1, passageSize * 2);
    boards[9].setCharacteristics(passageSize, passageSize*4, 1, passageSize * 2);
    boards[10].setCharacteristics(passageSize, passageSize*6, passageSize, 1);


    boards[9].setCharacteristics(passageSize * 2, 0, 1, passageSize * 5);
    boards[10].setCharacteristics(passageSize * 3, passageSize, 1, passageSize * 4);
    boards[11].setCharacteristics(passageSize * 3, passageSize * 6, 1, passageSize);

    boards[12].setCharacteristics(passageSize * 4, 0, 1, passageSize);
    boards[13].setCharacteristics(passageSize * 4, passageSize * 2, 1, passageSize*5);
    boards[14].setCharacteristics(passageSize * 4, passageSize, passageSize, 1);

    boards[15].setCharacteristics(passageSize * 5, passageSize * 2, 1, passageSize*4);
    boards[16].setCharacteristics(passageSize * 6, passageSize, passageSize * 3, 1);
    boards[17].setCharacteristics(passageSize * 6, passageSize, 1, passageSize);
    boards[18].setCharacteristics(passageSize * 6, passageSize*3, 1, passageSize*3);
    boards[19].setCharacteristics(passageSize * 7, passageSize, passageSize*2, 1);
    boards[20].setCharacteristics(passageSize * 7, passageSize*2, 1, passageSize);
    boards[21].setCharacteristics(passageSize * 7, passageSize*3, passageSize, 1);
    boards[22].setCharacteristics(passageSize * 7, passageSize*4, passageSize, 1);
    boards[23].setCharacteristics(passageSize * 7, passageSize * 5, 1, passageSize);
    boards[24].setCharacteristics(passageSize * 7, passageSize * 6, passageSize, 1);
    boards[25].setCharacteristics(passageSize * 8, passageSize * 3, 1, passageSize);
    boards[26].setCharacteristics(passageSize * 8, passageSize * 5, passageSize, 1);
    boards[27].setCharacteristics(passageSize * 8, passageSize * 5, 1, passageSize);

    boards[28].setCharacteristics(passageSize, passageSize * 4, 1, passageSize * 2);
    boards[29].setCharacteristics(passageSize, passageSize * 6, passageSize, 1);
    boards[30].setCharacteristics(passageSize*3, passageSize * 5, passageSize, 1);
    boards[31].setCharacteristics(passageSize*4, passageSize * 2, passageSize,1);
    boards[32].setCharacteristics(passageSize*7, passageSize * 2, passageSize*2, 1);










    //boards[19].setCharacteristics(passageSize * 6, passageSize, passageSize,1);
    //boards[21].setCharacteristics(passageSize * 6, passageSize * 3, 1, passageSize * 2);
    //boards[20].setCharacteristics(passageSize * 7, passageSize, 1, passageSize);










    // СТЕНЫ ВНУТРИ КАРТЫ


}

std::pair<std::pair<double, double>, int> solveX(const double& a, const double& b, const double& c)
{
    double D = b * b - 4 * a * c;
    if (D < 0) return std::make_pair(std::make_pair(0, 0), 0);
    if (D = 0)return std::make_pair(std::make_pair(-b / 2 / a, 0), 1);
    if (D > 0)return std::make_pair(std::make_pair((-b - sqrt(D)) / 2 / a, (-b + sqrt(D)) / 2 / a), 2);
}
double findDistance(const coordinates& A, const coordinates& B, const coordinates& C) {
    //зададим прямую BC
    //ax+by+c=0

    double c, b, a;
    if (C.y == B.y) {
        a = 0;
        b = 1;
        c = -B.y;
    }
    else {
        a = 1;
        c = (-B.x * C.y + B.y * C.x) / (C.y - B.y);
        b = (-c - B.x) / B.y;
    }


    double dist = (a * A.x + b * A.y + c) / sqrt(a * a + b * b);

    return (dist > 0) ? dist : -dist;
    
}
double findNeighbour(const coordinates& A, const double& angle, const rect& rectangle) {
    double dist = mapSizeX;

    double len = mapSizeX;

    coordinates AB;
    AB.x = len * cos(angle * pi / 180);
    AB.y = -len * sin(angle * pi / 180);

    coordinates CD;

    coordinates AC;
    coordinates AD;

    coordinates CA;
    coordinates CB;

    coordinates P;
    double Z1, Z2;

    for (int i = 0; i < 4; ++i)
    {
        int j = (i + 1) % 4;

        bool flag = 0;

        AC.x = rectangle.xy[i].x - A.x;
        AC.y = rectangle.xy[i].y - A.y;

        AD.x = rectangle.xy[j].x - A.x;
        AD.y = rectangle.xy[j].y - A.y;

        Z1 = AB.x * AC.y - AB.y * AC.x;
        Z2 = AB.x * AD.y - AB.y * AD.x;

        flag = ((Z1 * Z2) < 0);

        if (flag)
        {

            CA.x = -AC.x;
            CA.y = -AC.y;

            CB.x = A.x + len * cos(angle * pi / 180) - rectangle.xy[i].x;
            CB.y = A.y - len * sin(angle * pi / 180) - rectangle.xy[i].y;

            CD.x = rectangle.xy[j].x - rectangle.xy[i].x;
            CD.y = rectangle.xy[j].y - rectangle.xy[i].y;

            flag = (((CD.x * CA.y - CD.y * CA.x) * (CD.x * CB.y - CD.y * CB.x)) < 0);
            if (flag)
            {
                double Z = ((Z1 / (Z2 - Z1)) > 0) ? Z1 / (Z2 - Z1) : -Z1 / (Z2 - Z1);

                P.x = rectangle.xy[i].x + (rectangle.xy[j].x - rectangle.xy[i].x) * Z;
                P.y = rectangle.xy[i].y + (rectangle.xy[j].y - rectangle.xy[i].y) * Z;

                double dist1 = sqrt(pow(P.x - A.x, 2) + pow(P.y - A.y, 2));

                dist = ((dist1 < dist)) ? dist1 : dist;
            }
        }
    }
    return dist;
}
double findNeighbour(const coordinates& A, const double& angle, const std::vector<rect>& rects, coordinates& C, coordinates& D)
{
    double dist = mapSizeX;

    double len = mapSizeX;

    coordinates AB;
    AB.x = len * cos(angle * pi / 180);
    AB.y = -len * sin(angle * pi / 180);

    coordinates CD;

    coordinates AC;
    coordinates AD;

    coordinates CA;
    coordinates CB;

    coordinates P;
    double Z1, Z2;

    for (rect rectangle : rects)
    {
        for (int i = 0; i < 4; ++i)
        {
            int j = (i + 1) % 4;

            bool flag = 0;

            AC.x = rectangle.xy[i].x - A.x;
            AC.y = rectangle.xy[i].y - A.y;

            AD.x = rectangle.xy[j].x - A.x;
            AD.y = rectangle.xy[j].y - A.y;

            Z1 = AB.x * AC.y - AB.y * AC.x;
            Z2 = AB.x * AD.y - AB.y * AD.x;

            flag = ((Z1 * Z2) < 0);

            if (flag)
            {

                CA.x = -AC.x;
                CA.y = -AC.y;

                CB.x = A.x + len * cos(angle * pi / 180) - rectangle.xy[i].x;
                CB.y = A.y - len * sin(angle * pi / 180) - rectangle.xy[i].y;

                CD.x = rectangle.xy[j].x - rectangle.xy[i].x;
                CD.y = rectangle.xy[j].y - rectangle.xy[i].y;

                flag = (((CD.x * CA.y - CD.y * CA.x) * (CD.x * CB.y - CD.y * CB.x)) < 0);
                if (flag)
                {
                    double Z = ((Z1 / (Z2 - Z1)) > 0) ? Z1 / (Z2 - Z1) : -Z1 / (Z2 - Z1);

                    P.x = rectangle.xy[i].x + (rectangle.xy[j].x - rectangle.xy[i].x) * Z;
                    P.y = rectangle.xy[i].y + (rectangle.xy[j].y - rectangle.xy[i].y) * Z;

                    double dist1 = sqrt(pow(P.x - A.x, 2) + pow(P.y - A.y, 2));
                    if (dist1 < dist)
                    {
                        dist = dist1;
                        C.x = rectangle.xy[i].x;
                        C.y = rectangle.xy[i].y;
                        D.x = rectangle.xy[j].x;
                        D.y = rectangle.xy[j].y;
                    }
                }
            }
        }
    }
    return dist;
}
double findNeighbour(const coordinates& A, const double& angle, const std::vector<rect>& rects)
{
    double dist = mapSizeX;

    double len = mapSizeX;

    coordinates AB;
    AB.x = len * cos(angle * pi / 180);
    AB.y = -len * sin(angle * pi / 180);

    coordinates CD;

    coordinates AC;
    coordinates AD;

    coordinates CA;
    coordinates CB;

    coordinates P;
    double Z1, Z2;

    for (rect rectangle : rects)
    {
        for (int i = 0; i < 4; ++i)
        {
            int j = (i + 1) % 4;

            bool flag = 0;

            AC.x = rectangle.xy[i].x - A.x;
            AC.y = rectangle.xy[i].y - A.y;

            AD.x = rectangle.xy[j].x - A.x;
            AD.y = rectangle.xy[j].y - A.y;

            Z1 = AB.x * AC.y - AB.y * AC.x;
            Z2 = AB.x * AD.y - AB.y * AD.x;

            flag = ((Z1 * Z2) < 0);

            if (flag)
            {

                CA.x = -AC.x;
                CA.y = -AC.y;

                CB.x = A.x + len * cos(angle * pi / 180) - rectangle.xy[i].x;
                CB.y = A.y - len * sin(angle * pi / 180) - rectangle.xy[i].y;

                CD.x = rectangle.xy[j].x - rectangle.xy[i].x;
                CD.y = rectangle.xy[j].y - rectangle.xy[i].y;

                flag = (((CD.x * CA.y - CD.y * CA.x) * (CD.x * CB.y - CD.y * CB.x)) < 0);
                if (flag)
                {
                    double Z = ((Z1 / (Z2 - Z1)) > 0) ? Z1 / (Z2 - Z1) : -Z1 / (Z2 - Z1);

                    P.x = rectangle.xy[i].x + (rectangle.xy[j].x - rectangle.xy[i].x) * Z;
                    P.y = rectangle.xy[i].y + (rectangle.xy[j].y - rectangle.xy[i].y) * Z;

                    double dist1 = sqrt(pow(P.x - A.x, 2) + pow(P.y - A.y, 2));

                    dist = ((dist1 < dist)) ? dist1 : dist;
                }
            }
        }
    }
    return dist;
}

coordinates findSpeed(player& player1, const std::vector<rect>& boards) {
    double angle = player1.angle * pi / 180;
    double dist = 0;
    int j = 0;
    double perpendicularVecAngle = 0;
    double newAngle = 0;
    double projection = 0;

    coordinates resultSpeed = coordinates(player1.speedX, player1.speedY);
    coordinates perpendicularVec;

    coordinates A, B;
    dist = findNeighbour(player1.location, player1.angle, boards, A, B);
    double playerSpeed = sqrt(player1.speedX * player1.speedX + player1.speedY * player1.speedY);
    if (playerSpeed >= sqrt(resultSpeed.x * resultSpeed.x + resultSpeed.y * resultSpeed.x)) {
        resultSpeed = resultSpeed * (dist / playerSpeed);
        coordinates AB(B - A);
        //sqrt((playerSpeed.x+x)^2+(playerSpeed.y+x*AB.y/AB.x)^2)=mapSizeX/10
        double a = playerSpeed * cos(angle);
        double b = playerSpeed * sin(angle);
        if (AB.x != 0)
        {
            double m = AB.y / AB.x;

            auto x = solveX(m * m + 1, 2 * (a + b * m), a * a + b * b - mapSizeX * mapSizeX / 10000);
            if (x.second == 2)
            {
                resultSpeed.x += x.first.first;
                resultSpeed.y += x.first.first * m;
            }
            if (x.second == 1)
            {
                resultSpeed.x += x.first.first;
                resultSpeed.y += x.first.first * m;
            }
        }
        else {
            resultSpeed.x += 0;
            resultSpeed.y += sqrt(mapSizeX * mapSizeX / 10000. - a * a) - b;
        }

    }

    return resultSpeed;

    //for (int i = 0; i < countRays; ++i)
    /*

        //angle += 360 / countRays;
        for (rect rectangle : boards)
        {
            for (int i = 0; i < 4; ++i)
            {
                j = (i + 1) % 4;
                CD.x = rectangle.xy[j].x - rectangle.xy[i].x;
                CD.y = rectangle.xy[j].y - rectangle.xy[i].y;
                if (CD.y == 0) {
                    perpendicularVec.x = 0;
                    perpendicularVec.y = 1;
                    perpendicularVecAngle = -pi/2;
                }
                else {
                    perpendicularVec.x = 1;
                    perpendicularVec.y = -CD.x * 1 / CD.y;

                    perpendicularVecAngle = atan(perpendicularVec.y / perpendicularVec.x);

                }

                newAngle = perpendicularVecAngle - angle;

                projection = (mapSizeX / 10) * cos(newAngle);

                    dist = findDistance(player1.location, rectangle.xy[i], rectangle.xy[j]);
                    if (projection > dist)
                        projection = dist;
                    if (-projection > dist) projection = -dist;

                    perpendicularVec.x = projection * cos(perpendicularVecAngle);
                    perpendicularVec.y = projection * sin(perpendicularVecAngle);
                    resultSpeed += perpendicularVec;

            }
        }
    */
    //return resultSpeed;
}
