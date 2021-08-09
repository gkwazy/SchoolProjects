//
//  DeckOfCards.cpp
//  DeskOfCards
//
//  Created by Garret Wasden on 9/1/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//
//The first step is to come up with a representation for a playing card. Define a struct representing a card. Hint: I'd suggest storing the "rank" of the card as an integer, where a Jack is 11, Queen is 12, etc. When you print out a card, you can take this into consideration and print K instead of 13, for example. Another option would be to store the rank as a char.
//
//Write a function to create a deck of cards. Just like a deck of cards you buy from the store, it's probably easiest to create this deck so that the cards are sorted in some order. You might (or might not) want to create a struct to represent the deck. Think about the pros/cons before deciding.
//
//Write a function to print a deck of cards. Verify in main that you are able to create and print a deck of cards.
//
//Keep in mind that we'll be building on this assignment for the next few days, so make sure you're code is in a good state!

#include<vector>
#include<cstdlib>
#include "DeckOfCards.hpp"

using namespace std;

vector<card> Deck(){
    vector<string> suits = {"Spades","Club","Hearts","Diamonds"};
    vector<card> deckVector;
    char color;
    for(string suit: suits){
        for(int i = 2; i <= 14; i++){
            color = 'r';
            if (suit == suits[0] || suit == suits[1]){
                color = 'b';
            }
            card tempCard {i, color, suit};
            deckVector.push_back(tempCard);
        }
    }
    return deckVector;
}

string CardsString(vector<card> deck){
    string cardsString = "";
    string singleCard = "";
    for(int i = 0; i < deck.size(); i++){
        singleCard = to_string(deck[i].Number) +" of "+ deck[i].suit;
        cardsString = cardsString + singleCard + ", ";
    }
    return cardsString;
}

void shuffleDeck (vector<card> &deck){
    long size = deck.size();
    srand( static_cast<unsigned int>(time(nullptr)));
    for ( int i = 0; i < size-1; i++){
        int randomNum = rand() % (size-i);
        swap(deck[i], deck[randomNum]);
    }
}

vector<int> sortHand(vector<card> playerHand){
    vector<int> numberVector;
    for (int i = 0; i < playerHand.size();i++){
        numberVector.push_back(playerHand[i].Number);
    }
    sort(numberVector.begin(), numberVector.end());
    return numberVector;
}

bool isFlush(vector<card> playerHand){
    for(int i = 1; i < playerHand.size();i++){
        if (playerHand[i].suit != playerHand[0].suit){
            return false;
        }
    }
    return true;
}

bool isStraight(vector<card> playerHand){
//sorting the hand with selection sorting.
    vector<int> numberVector = sortHand(playerHand);
    for (int i = 0; i < numberVector.size()-1; i++) {
        if (numberVector[i+1]!= (numberVector[i] + 1)){
            return false;
        }
    }
    return true;
}
//
bool isStraightFlush(vector<card> playerHand){
    if ( isStraight(playerHand) == true && isFlush(playerHand) == true){
        return true;
    }
    return false;
}

bool isRoyalFlush(vector<card> playerHand){
   vector<int> playerHandNumbers = sortHand(playerHand);
    if(isFlush(playerHand) == true && playerHandNumbers[playerHandNumbers.size()] == 14) {
            return true;
        }
    return false;
}
       
bool FullHouse( vector<card> playerHand){
       vector<int> playerHandNumbers = sortHand(playerHand);
    
        if (playerHandNumbers[0]==playerHandNumbers[1] && playerHandNumbers[2]==playerHandNumbers[3]
            &&playerHandNumbers[3]==playerHandNumbers[4]){
            return true;
        }
        if (playerHandNumbers[0]==playerHandNumbers[1] && playerHandNumbers[1]==playerHandNumbers[2]
            &&playerHandNumbers[3]==playerHandNumbers[4]){
            return true;
        }
        return false;
    }

