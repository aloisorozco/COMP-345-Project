#include "Cards.h"
#include "../Orders/Orders.h"
#include <iostream>
using namespace std;
void testCards(){
    vector<Card*> cardsToRemove; //solution to play() error and for loops
    //1.make a deck object, will call initialize() and add a cards to it.
    Deck* deck = new Deck();
    cout<<*deck;
    //2.a.Create hand with ref to the deck.
    Hand* hand = new Hand(deck);
    Hand* hand2 =new Hand(deck);
    //2.b.Draw cards, which adds them to hand
    for(int i =0; i< 5; i++){
        deck->draw(&hand);   //ref to hand.
    }
    //testing for an extra player hand
    for(int i =0; i< 5; i++){
        deck->draw(&hand2);   //ref to hand.
    }
    cout<<*hand;
    //second player hand works
    cout<<*hand2;
    cout<<*deck;

    //3.a.play cards from only hand 1(
    cout <<"\nPLAY CARDS(add to deck, remove from hand)"<<endl;
    for(Card* card: hand->getCards()){
        //store the cards we're removing,
        // another approach caused bugs
        cardsToRemove.push_back(card);
    }
    for(Card* card : cardsToRemove){
        //play the cards(return deck, remove hand)
        card->play(&deck,&hand);
    }
    //done playing cards
    //3.b. Check all cards back in deck.
    cout<<*deck;
    cout<<*hand;
    //Test error, hand empty no cards to play
    try{
        cout <<"Check empty hand "<< hand->getCards().at(0)->cardTypeToString() <<endl;
        hand->getCards().front()->play(&deck, &hand);
    }
    catch(runtime_error& e){
        cerr << "Caught : "<< e.what()<<endl;
    }
    //deconstruct classes
    hand->~Hand();//deletes the cards within and clears the vector
    deck->~Deck();//deletes the cards within and clears the vector
    //issue command to break out of the program
    while(true){
        cout << "Enter command: (for now 'end' will exit) ";
        string command;
        cin >> command;
        if (command == "end") {
            std::cout<<"Game ended";
            break;
        }
    }


}
