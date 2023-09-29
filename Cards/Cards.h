#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>
using namespace std;

//Forward declarations is good practice
class Card;
class Deck;
class Hand;
//The card Types
enum class CardType {
    Bomb,
    Reinforcement,
    Blockade,
    Airlift,
    Diplomacy
};
/*
 * REQUIREMENTS FOR A1
 * draw() -> draw a card from deck, remove from deck
 * returnCard() -> play() needs to return the card to deck
 */
class Deck {
public:
	Deck();
    Card draw();
    void returnCard(Card& card);
private:
    vector<Card> cards;
    void initializeDeck();
};
/*
 * Draw card -> addCard to hand.
 */
class Hand {
public:
    explicit Hand(int handSize);
    int handSize;
	void addCard(Card card);
    const vector<Card>& getCards() const;
private:
    vector<Card> cards;
};
/*
 * REQUIREMENTS FOR A1
 * play() -> play a card.
 */
class Card{
public:
    explicit Card(CardType type);
    void play(Deck& deck);
    CardType getType() const;
    string cardTypeToString() const;
private:
    CardType type;
};
#endif