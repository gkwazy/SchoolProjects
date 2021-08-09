//
//  Encrypt.hpp
//  CryptoHomeWork 1
//
//  Created by Garret Wasden on 3/5/21.
//

#ifndef Encrypt_hpp
#define Encrypt_hpp

#include <stdio.h>
#include <string>
#include <array>

class Encrypt{
    std::array<std::array<uint8_t,256>,8> subTables;
    
public:
    Encrypt();
    std::vector<uint8_t> messageEncrypt(std::string password, std::string message);
    std::string messageDecrypt(std::string password, std::vector<uint8_t> message);

private:
    
    static std::array<uint8_t,8> hashPassword(std::string password);
    static void seedStartingTable(std::array<std::array<uint8_t,256>,8> &masterTable);
    static void generateTables(std::array<uint8_t,256>);
    static void fisherShuffle(std::array<uint8_t,256> &table);
    static void xorMessage(std::vector<uint8_t> &message,std::array<uint8_t,8> key);
    static void deXorMessage(std::vector<uint8_t> &message,std::array<uint8_t,8> key);
    void tableSub(std::vector<uint8_t> &message);
    void tableDeSub(std::vector<uint8_t> &message);
    void bitShift(std::vector<uint8_t> &message);
    void bitDeShift(std::vector<uint8_t> &message);
    
};


class RC4{
public:
    RC4();
    std::string rc4Encrypt(std::string message,std::array<int,8> key);
    std::string rc4Decrypt(std::string message,std::array<int,8> key);
private:
    std::vector<int> rc4PartOne(std::array<int,8> key);
    std::vector<uint8_t> rc4PartTwo(std::vector<uint8_t> message, std::vector<int> state);
};

#endif /* Encrypt_hpp */
