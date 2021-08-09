//
//  Encrypt.cpp
//  CryptoHomeWork 1
//
//  Created by Garret Wasden on 3/5/21.
//

#include "Encrypt.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <array>


Encrypt::Encrypt(){
    seedStartingTable(subTables);
    
}

std::array<uint8_t,8> Encrypt::hashPassword(std::string password){
    std::array<uint8_t,8> key = {0,0,0,0,0,0,0,0};
    for(int i = 0; i<password.length(); i++){
        key[i % 8] = key[i % 8] xor password[i];
    }
    return key;
};

std::vector<uint8_t> Encrypt::messageEncrypt(std::string password, std::string message){
    std::array<uint8_t,8> key = hashPassword(password);
    std::vector<uint8_t> messageVector(message.begin(), message.end());
    
    
    
    for(int i = 0; i < 16; i++){
        xorMessage(messageVector, key);
        tableSub(messageVector);
        bitShift(messageVector);
       
        
    };
    return messageVector;
};

std::string Encrypt::messageDecrypt(std::string password, std::vector<uint8_t> message){
    std::array<uint8_t,8> key = hashPassword(password);
    for(int i = 0; i < 16; i++){
        bitDeShift(message);
        tableDeSub(message);
        deXorMessage(message, key);
    };
    std::string messageString(message.begin(),message.end());
    return messageString;
    
    
}

 void Encrypt::seedStartingTable(std::array<std::array<uint8_t,256>,8> &masterTable){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 256; j++){
            masterTable[i][j] = j;
        };
        fisherShuffle(masterTable[i]);
    };
};

void Encrypt::fisherShuffle(std::array<uint8_t,256> &table){
    int randNum = 0;
    uint8_t temp;
    for(int i = 255; i > 0 ; i--){
        randNum = rand() % i;
        temp = table[randNum];
        table[randNum] = table[i];
        table[i] = temp;
    }
};

void Encrypt::xorMessage(std::vector<uint8_t> &message, std::array<uint8_t,8> key){
    for(int i = 0; i < message.size(); i++){
        message[i] = message[i] xor key[i % 8];
    }
};

void Encrypt::deXorMessage(std::vector<uint8_t> &message, std::array<uint8_t,8> key){
    for(int i = 0; i < message.size(); i++){
        message[i] = key[i % 8] xor message[i];
    }
};

void Encrypt::tableSub(std::vector<uint8_t> &message){
    for(int i = 0; i < message.size(); i++){
        message[i] = subTables[i % 8][message[i]];
    };
};

void Encrypt::tableDeSub(std::vector<uint8_t> &message){
    for(int i = 0; i < message.size(); i++){
        for(int j = 0; j < 256; j++){
            if (subTables[i % 8][j] == message[i]){
                message[i] = (uint8_t)j;
                break;
            }
        };
    };
};

void Encrypt::bitShift(std::vector<uint8_t> &message){
    uint8_t tempFront;
    uint8_t frontMask = 0x80;
    uint8_t tempshift;
    tempFront = message[0] & frontMask;
    tempFront = tempFront >> 7;
    
    
    for (int i = (int)(message.size() - 1); i >= 0; i--){
        tempshift = message[i] & frontMask;
        tempshift = tempshift >> 7;
        message[i] = (message[i] << 1) xor tempFront;
        tempFront = tempshift;
       
        
    }
};

void Encrypt::bitDeShift(std::vector<uint8_t> &message){
    uint8_t tempFront;
    uint8_t frontMask = 0x01;
    uint8_t tempshift;
    tempFront = message[message.size() - 1] & frontMask;
    tempFront = tempFront << 7;
    for (int i = 0; i < message.size(); i++){
        tempshift = message[i] & frontMask;
        tempshift = tempshift << 7;
        message[i] = (message[i] >> 1) xor tempFront;
        tempFront = tempshift;
    }
}

RC4::RC4(){
    
};

std::string RC4::rc4Encrypt(std::string message, std::array<int,8> key){
    std::vector<int> stateVec = rc4PartOne(key);
    
    std::vector<uint8_t> messageVector(message.begin(), message.end());
    std::vector<uint8_t> stateEncrypt = rc4PartTwo(messageVector, stateVec);
    
    for(int i = 0; i < messageVector.size(); i++){
        messageVector[i] = messageVector[i] xor stateEncrypt[i % 256];
    }
    std::string encryptString(messageVector.begin(),messageVector.end());
    
//    for(int i = 0; i < messageVector.size(); i++){
//        printf("%x ", messageVector[i]);
//    }
//    printf("\n");
    
    return encryptString;
};


std::vector<int> RC4::rc4PartOne(std::array<int,8> key){
    std::vector<int> state;
    for(int i = 0; i < 256; i++){
        state.push_back(i);
    };
    int j = 0;
    int tempSwap;
    for ( int i = 0; i < 255; i++){
        j = (j + state[i] + key[i % key.size()]) % 256;
        tempSwap = state[i];
        state[i] = state[j];
        state[j] = tempSwap;
    }
    return state;
};

std::vector<uint8_t> RC4::rc4PartTwo(std::vector<uint8_t> message, std::vector<int> state){
    int j = 0;
    std::vector<uint8_t> stateKey;
    int tempSwap;
    int stateSwap;
    for (int h = 0; h < message.size(); h++){
        int i = h % 256;
        j = (j + state[i]) % 256;
        tempSwap = state[i];
        state[i] = state[j];
        state[j] = tempSwap;
        stateSwap = (state[i] + state[j]) % 256;
        stateKey.push_back(state[stateSwap]);
    }
    return stateKey;
};
