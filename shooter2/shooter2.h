#pragma once

#include <SFML/Graphics.hpp>
#include<vector>
#include"objects.h"
#include<iostream>
#include"player.h"
#include"variables.h"

#include<SFML/Network.hpp>
#include<string>
#include<Windows.h>
#include<fstream>




double findDistance(const coordinates& A, const coordinates& B, const coordinates& C);
double findNeighbour(const coordinates& A, const double& angle, const rect& rectangle);
double findNeighbour(const coordinates& A, const double& angle, const std::vector<rect>& rects, coordinates& C, coordinates& D);
double findNeighbour(const coordinates& A, const double& angle, const std::vector<rect>& rects);

coordinates findSpeed(player& player1, const std::vector<rect>& boards);


void map(const sf::RenderWindow& window, std::vector<rect>& boards);

