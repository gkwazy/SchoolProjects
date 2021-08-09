//
//  DeckOfCards.hpp
//  DeskOfCards
//
//  Created by Garret Wasden on 9/1/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef DeckOfCards_hpp
#define DeckOfCards_hpp


#include <stdio.h>
#include <string>
using namespace std;

struct card {
    int Number;
    char color;
    string suit;
};

vector<card> Deck();

string CardsString(vector<card> deck);
void shuffleDeck (vector<card> &deck);
bool isStraight(vector<card> playerHand);
bool FullHouse( vector<card> playerHand);
bool isRoyalFlush(vector<card> playerHand);
bool isStraightFlush(vector<card> playerHand);
bool isFlush(vector<card> playerHand);



#endif /* DeckOfCards_hpp */
