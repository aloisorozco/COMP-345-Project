#include "Cards.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "../Orders/Orders.h"

using namespace std;

Card::Card(CardType type) : type(type) {}
CardType Card::getType()const{
    return type;
}
string Card::cardTypeToString() const {
    if(type == CardType::Bomb){
        return "Bomb";
    }
    else if(type == CardType::Reinforcement){
        return "Reinforcement";
    }
    else if(type == CardType::Blockade){
        return "Blockade";
    }
    else if(type == CardType::Airlift){
        return "Airlift";
    }
    else if(type == CardType::Diplomacy){
        return "Diplomacy";
    }
    else{
        return "Error detecting Card Type";
    }
}
void Card::play(Deck& deck){
    cout <<"Playing a " << cardTypeToString() << " card." << endl;
    //Add card to Order list
    deck.returnCard(*this);
}
Deck::Deck(){
    initializeDeck();
}
//No idea what would trigger Draw method.
//In the game Risk, you draw one at end of turn if you captured territory.
Card Deck::draw(){
    //first we shuffle, then we draw.
    //not going to use shuffle() or some costly methods to randomize.
    if(!cards.empty()) {
        int randIndex = rand() % cards.size();
        Card card = cards[randIndex];
        cards.erase(cards.begin() + randIndex);
        cout<<"You drew the card: "<< card.cardTypeToString() << " card." << endl;
        return card;
    }
    else{
        //In theory this should happen if we draw the whole deck without playing cards.
        cout<<"EMPTY DECK ";
        throw runtime_error("EMPTY DECK ");
    }
}
//We want to return the Card after playing it.
void Deck::returnCard(Card& card) {
    cards.push_back(card);
}
//Game Start, put cards into Deck.
void Deck::initializeDeck() {
    //Put cards of all types into deck. NOT SHUFFLED
    //need to know how many cards in the deck(NOT SPECIFIED)
    int deckSize = 15;
    //emplace_back appends new element to the end
    for(int i =0; i<deckSize; i++){
        cards.emplace_back(CardType::Bomb);
        cards.emplace_back(CardType::Reinforcement);
        cards.emplace_back(CardType::Blockade);
        cards.emplace_back(CardType::Airlift);
        cards.emplace_back(CardType::Diplomacy);
    }
}
Hand::Hand(int handSize){
    //
    handSize = handSize;
};
void Hand::addCard(Card card) {
    cards.push_back(card);
}
const vector<Card>& Hand::getCards() const{
    return cards;
}