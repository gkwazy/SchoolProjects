//
//  main.cpp
//  CryptoHomeWork 1
//
//  Created by Garret Wasden on 3/5/21.
//

#include <iostream>
#include <vector>
#include "Encrypt.hpp"

int main(int argc, const char * argv[]) {
    std::string messageString;
    std::cout << "Enter Message: "<< std::endl;
//    messageString = "Kenob, bold as ever. hello as well there";
    getline(std::cin, messageString);

    std::string passwordString;
    std::cout << "Enter Password(min of 8 charaters): " << std::endl;
    getline(std::cin, passwordString);

    bool neededPassword = true;
    while(neededPassword){
        if (passwordString.length() >= 8){
            neededPassword = false;
            break;
        }
        std::cout << "Password to short\nEnter Password(min of 8 charaters): " << std::endl;
        getline(std::cin, passwordString);
    }

    Encrypt *encrypt = new Encrypt();
    std::vector<uint8_t> messageVector = encrypt->messageEncrypt(passwordString, messageString);

    std::string codeMessage(messageVector.begin(),messageVector.end());

    std::cout << "encoded: " << codeMessage << std::endl;

    std::string passwordDecode;
    std::cout << "Enter Password for Decoding: " << std::endl;
    getline(std::cin, passwordDecode);

    std::string deMessage = encrypt->messageDecrypt(passwordDecode, messageVector);

    std::cout << "decoded: " << deMessage << std::endl;
//
    
    std::cout << "Part Two RC4______\nEnter Message: "<< std::endl;
    getline(std::cin, messageString);
    RC4 *rc4 = new RC4();
    std::array<int,8> key = {0,1,2,3,4,5,6,7};
    std::array<int,8> key2 = {1,2,3,4,5,6,7,8};

    messageString = "Your salary is $1234";
    std::string evilString = "Your salary is $9999";
    
    std::string rcMessage = rc4->rc4Encrypt(messageString, key);
    std::cout << "\nencoded rc: " << rcMessage << std::endl;
    
    rcMessage = rc4->rc4Encrypt(rcMessage, key);
    std::cout << "\ndecoded rc: " << rcMessage << std::endl;

    rcMessage = rc4->rc4Encrypt(messageString, key);
    std::cout << "\nencodedw with key1: " << rcMessage << std::endl;

    rcMessage = rc4->rc4Encrypt(rcMessage, key2);
    std::cout << "\ndecoded with key2: " << rcMessage << std::endl;
    
    rcMessage = rc4->rc4Encrypt(messageString, key);
    std::cout << "\nencoded $$: " << rcMessage << std::endl;
//
    std::vector<uint8_t> encriptVector(rcMessage.begin(), rcMessage.end());
    std::vector<uint8_t> evilVector(evilString.begin(), evilString.end());
    std::vector<uint8_t> normalVector(messageString.begin(), messageString.end());

    
    for (int i = 0; i < evilVector.size() ; i++){
        evilVector[i] = normalVector[i] xor evilVector[i];
    };
    for (int i = 0; i < evilVector.size() ; i++){
        evilVector[i] = encriptVector[i] xor evilVector[i];
    };
    
    std::string evilOutString(evilVector.begin(), evilVector.end());
    
    rcMessage = rc4->rc4Encrypt(evilOutString, key);
    std::cout << "\nhacked $$: " << rcMessage << std::endl;

    return 0;
}
//printf("%02X ",messageVector[i]);
