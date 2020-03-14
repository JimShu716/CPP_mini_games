
#include <vector>
using namespace std;

enum Rank
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

enum Type
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

class Card
{
private:
    //current rank and type of the card
    Rank currRank;
    Type currType;

public:
    Card(Rank pRank, Type pType);
    int getValue();
    void displayCard();
};

class Hand
{
private:
    vector<Card> currCards;

public:
    void add(Card pCard);
    void clear();
    int getTotal() const;

    //helper method
    void getCards();
};

class Deck
{
private:
    vector<Card> currCards;

public:
    Deck() : currCards(){};

    void Populate();
    void shuffle();
    Card deal();
};

class AbstractPlayer : public Hand
{
private:
    vector<Card> currCards;

public:
    virtual bool isDrawing() const = 0;
    bool isBusted();
};

class ComputerPlayer : public AbstractPlayer
{
public:
    bool isDrawing() const override;
};

class HumanPlayer : public AbstractPlayer
{

public:
    bool isDrawing() const override;

    // This function checks and announces if a player wins
    void announce(ComputerPlayer);
};

class BlackJackGame
{
private:
    Deck m_deck;
    ComputerPlayer m_casino;

public:
    // Play the game for once
    void play();
};