#ifndef CARDS_H
#define CARDS_H
//#include "../Orders/Orders.h"
#include <vector>
#include <string>
using namespace std;

class Card;
class Deck;//forward declaration is good practice
class Hand;

class Deck { //Deck class contains Cards, players will draw cards with draw() and return cards returnCard()
public:
    Deck(); //default constructor
	Deck(const Deck&); //1. our copy constrctor
    Deck& operator =(const Deck&); //2.copy operator
    friend ostream& operator<<(ostream&,const Deck&);//3.stream insertion operator for output

    void draw(Hand **hand); // draws a card, removes it from deck adds it to hand
    void returnCard(Card* card); // played card is removed from hand, returned to deck
    //potential usage of getter/setter
    int getDeckSize()const;
    void setDeckSize(int s);
    ~Deck(); // deconstructor
private:
    vector<Card*> cards; //vector data type is best.Card* , user defined class data type is pointer
    int deckSize;
    void initializeDeck(); // quick method to add all cards to deck.
};

class Hand {//Hand class contains card drawn from Deck. Unique to each player.
public:
    explicit Hand(Deck*); // default constructor, taking card from the Deck.
    Hand(const Hand&); // 1.our copy constructor
    Hand& operator =(const Hand& hand);// 2. our copy operator
    friend ostream& operator<<(ostream&,const Hand&);//3.stream insertion operator for output

    void addCard(Card *card); // no need to modify so const
    void removeCard(Card *card);
    const vector<Card *> & getCards() const; //
    //Setter getter handsize might be useful later
    void setHandSize(int s);
    int getHandSize() const;
    ~Hand(); // deconstructor

private:
    //Temporary for adding orders on play()
    //OrdersList* ordersList;
    //the current hand size
    int handSize = 0;
    //maybe a max hand size later on??
    vector<Card*> cards; //we want pointers to cards
    //we want to delete these after in deconstructor
};

class Card{//Card class, different types of cards, play()
public:
    enum CardType {
        Bomb,
        Reinforcement,
        Blockade,
        Airlift,
        Diplomacy
    };
    Card(CardType type); //default constructor
    Card(const Card&); //copy constructor, const for no altering
    Card& operator =(const Card&); //Assignment operator of value of Card
    friend ostream& operator<<(ostream&, const Card&);//stream insertion operator for output

    void play(Deck **deck, Hand **hand); // The play function we need
    CardType getType() const;
    string cardTypeToString() const;
    ~Card(); //Deconstructor for destroying the card if ever needed later
private:
    CardType type;
};
#endif