#include "Cards.h"
#include <iostream>
void testCards(){
    Deck deck;
    int handSize = 7;
    Hand hand(handSize);
    //Hand Size for the game not specified yet.
    //Draw cards
    for(int i =0; i<hand.handSize; i++){
        Card drawnCard = deck.draw();
        hand.addCard(drawnCard);
    }
    //A1 wanted draw and play seperated
    for(Card card : hand.getCards()){
        card.play(deck);
    }
}
int main(){
    testCards();
    return 0;
}