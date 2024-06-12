//
// Created by buldu on 12.06.2024.
//

#include <iostream>
#include <sql.h>
#include "playersignin.h"






playersignin::~playersignin() {
    std::string username;
    std::string password;
    std::string email;

     //get from console
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;
    std::cout << "Enter your email: ";
    std::cin >> email;
}




