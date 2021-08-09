//
//  main.cpp
//  DeskOfCards
//
//  Created by Garret Wasden on 9/1/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//Write a function to create a deck of cards. Just like a deck of cards you buy from the store, it's probably easiest to create this deck so that the cards are sorted in some order. You might (or might not) want to create a struct to represent the deck. Think about the pros/cons before deciding.

//Write a function to print a deck of cards. Verify in main that you are able to create and print a deck of cards.

#include <iostream>
#include<string>
#include<vector>
#include "DeckOfCards.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<card> myDeck = Deck();
    shuffleDeck(myDeck);
    
    string cards = CardsString(myDeck);
    cout << cards << endl;
    vector<card> playerHand;
//dealing the top five cards to the player
    for (int i = 0; i < 5; i++){
        playerHand.push_back(myDeck[i]);
    }
   cout << " Players Hand: " <<CardsString(playerHand) << endl;
    
    if (isRoyalFlush(playerHand)){
            cout << "Royal Flush!!!!"<<endl;
    }

    else if (FullHouse(playerHand)){
            cout << "Full House"<<endl;
    }

    else if ( isFlush (playerHand)){
            cout << " Flush"<<endl;
    }

    else if (isStraight(playerHand)){
        cout << "Straight"<<endl;
    }
    else{
        cout << "No Hand"<<endl;
    }
    
int royalFlush = 0, fullHouse = 0, flush = 0, straight = 0, noHand = 0;
for ( int i = 0; i < 100000; i++) {

    if (isRoyalFlush(playerHand)){
        royalFlush++;
    }

    else if (FullHouse(playerHand)){
        fullHouse++;
    }
    else if ( isFlush (playerHand)){
        flush++;
    }

    else if (isStraight(playerHand)){
        straight++;
    }
    else{
        noHand++;
    }

 }
//        cout<< "Royal Flush: " << royalFlush << "\n"
//        << "Full House: "<< FullHouse<< "\n"
//        << "Flush: "<< flush<< "\n"
//        << "Straight: " << straight<< "\n"
//    << "No hand: "<< noHand <<"\n";
    return 0;
}
