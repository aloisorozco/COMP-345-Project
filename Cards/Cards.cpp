#include "Cards.h"
#include "../Orders/Orders.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
//////////CARD////////////////
Card::Card(CardType type) : type(type) {}
//Documentation on copy constructor follows this format
Card::Card(const Card& other) : type(other.type) {}
//assignment operator
Card &Card::operator=(const Card &) {
    return *this;
}
//stream insertion
ostream &operator<<(ostream& out, const Card& card) {
    out <<"card type = " << card.cardTypeToString() << endl;
    return out;
}
Card::CardType Card::getType() const{
    return type;//returns numbers 0-4(5 types of cards)
}
string Card::cardTypeToString() const {
    //check type, return the string value
    if(type == CardType::BombCT){
        return "Bomb";
    }
    else if(type == CardType::ReinforcementCT){
        return "Reinforcement";
    }
    else if(type == CardType::BlockadeCT){
        return "Blockade";
    }
    else if(type == CardType::AirliftCT){
        return "Airlift";
    }
    else if(type == CardType::DiplomacyCT){
        return "Diplomacy";
    }
    else{
        return "Error detecting Card Type : " + to_string(static_cast<int>(type));
    }
}
//check hand size, to make sure a card can be played
Order* Card::play(Deck *deck, Hand *hand){
    if((*hand).getHandSize() == 0){
        cout <<"No cards to play."<<endl;
        return NULL;
    }
    cout <<"Playing a " << this->cardTypeToString() << " card." << endl;
    Order* order; // play() creates an order outside not to get deleted
    if(type == CardType::BombCT){
        order = new Bomb(); //havent fetched/merged Order
        cout<<"Creating new Bomb Order to Order List\n";
        (*hand).getOrdersList().add(*order);
    }
    else if(type == CardType::ReinforcementCT){
        //This adds +5 units to your pool of deployable units.
        order = new Deploy();
        cout<<"Creating new Reinforcement Order to Order List\n";
        (*hand).getOrdersList().add(*order);
    }
    else if(type == CardType::BlockadeCT){
        order = new Blockade();
        cout<<"Creating new Blockade Order to Order List\n";
        (*hand).getOrdersList().add(*order);
    }
    else if(type == CardType::AirliftCT){
        order = new Airlift();
        cout<<"Creating new Airlift Order to Order List\n";
        (*hand).getOrdersList().add(*order);
    }
    else if(type == CardType::DiplomacyCT){
        order = new Negotiate();
        cout<<"Creating new Diplomacy Order to Order List\n";
        (*hand).getOrdersList().add(*order);
    }
    //print the card played
    (*deck).returnCard(this);
    (*hand).removeCard(this);
    return order;
}
//Deconstructor, but Deck and Hand already clear the cards
Card::~Card() = default;

/////////////////////DECK//////////////////////////
Deck::Deck(){
    initializeDeck(); // just adds cards to deck
}
//copy constructor
Deck::Deck(const Deck& copyDeck) {
    this->cards = copyDeck.cards;
    this->deckSize = copyDeck.deckSize;
}
//assignment operator
Deck &Deck::operator=(const Deck& copyDeck) {
    this->cards = copyDeck.cards;
    this->deckSize = copyDeck.deckSize;
    return *this;
}
//stream insertion
ostream &operator<<(ostream& out, const Deck& deck) {
    out << "\nCards left in deck:" <<endl;
    for(const Card* card : deck.cards){
        out <<"Card type: " << card->cardTypeToString()<<endl;
    }
    return out;
}
//No idea what would trigger Draw method.
//In the game Risk, you draw one at end of turn if you captured territory.
void Deck::draw(Hand *hand){
    //first we shuffle, then we draw.
   if(!cards.empty()) {
        int randIndex = rand() % cards.size(); // rand() generates same numbers, fine for now
        auto card = cards.begin() + randIndex;
        Card* drawncard = *card;
        cout<<"You drew the card: "<< drawncard->cardTypeToString() << " card." << endl;
        hand-> addCard(drawncard);
        cards.erase(card);
   }
    else{
        //In theory this should happen if we draw the whole deck without playing cards.
        cout<<"EMPTY DECK "<<endl;
        throw runtime_error("EMPTY DECK ");
    }
}
//We want to return the Card after playing it.
void Deck::returnCard(Card* card) {
    cards.push_back(card);
}
//Game Start, put cards into Deck.
void Deck::initializeDeck() {
    //Put cards of all types into deck. NOT SHUFFLED
    //need to know how many cards in the deck(NOT SPECIFIED)
    // or if it's going to be a user defined amount(input)
    int temp = 2;
    setDeckSize(temp);
    //emplace_back appends new element to the end
    for(int i =0; i<deckSize; i++){
        cards.emplace_back(new Card(Card::BombCT));
        cards.emplace_back(new Card(Card::ReinforcementCT));
        cards.emplace_back(new Card(Card::BlockadeCT));
        cards.emplace_back(new Card(Card::AirliftCT));
        cards.emplace_back(new Card(Card::DiplomacyCT));
    }
}

Deck::~Deck() {
    for(auto & card : cards){
        delete card; // delete the Card pointers in the vector
    }
    cards.clear(); // clear the vector
}

int Deck::getDeckSize() const {
    return cards.size();
}

void Deck::setDeckSize(int s) {
    deckSize =s;
}
///////////////HAND//////////////////

Hand::Hand(Deck* deck){
    //need to add play() cards to OrderList
    ordersList = new OrdersList();
}
Hand::Hand(const Hand& copyHand) {
}

const vector<Card *> & Hand::getCards() const {
    if(cards.empty()){
        //prevent getting from empty hand.
        throw runtime_error("No cards in hand");
    }
    return cards;
}
void Hand::addCard(Card *card) {
    cards.push_back(card);
    handSize++;
}

Hand& Hand::operator=(const Hand& hand) {
    return *this;
}

ostream &operator<<(ostream& out, const Hand& hand) {

    out <<"\nNumber of cards in hand: "<<hand.handSize<<"\ncards in hand : "<<endl;
    for (auto card : hand.cards) {
        out <<"Card type: "<< card->cardTypeToString()<<endl ;
    }
    return out;
}

Hand::~Hand() {
    for(Card* card: cards){
        delete card;
    }
    cards.clear();

    delete this->ordersList;
    ordersList = NULL;
}

int Hand::getHandSize() const {
    return handSize;
}

void Hand::setHandSize(int s) {
    handSize =s;
}

void Hand::removeCard(Card* card) {
    auto index = find(cards.begin(), cards.end(), card);
    if(index != cards.end()){
        cards.erase(index);
        //card = nullptr;
        handSize--;
    }

}

OrdersList Hand::getOrdersList()const {
    return *this->ordersList;
}




