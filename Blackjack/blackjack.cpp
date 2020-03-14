
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include "blackjack.h"

using namespace std;

Card::Card(Rank pRank, Type pType)
{
    this->currRank = pRank;
    this->currType = pType;
}

int Card::getValue()
{
    //    return currRank;
    if (currRank <= 10)
    {
        return currRank;
    }
    else
    {
        return 10;
    }
}

void Card::displayCard()
{
    string R;
    int score = this->currRank;
    switch (score)
    { //I cannot use to_String as the trottier machine does not support it
    case 1:
        R = "1";
        break;
    case 2:
        R = "2";
        break;
    case 3:
        R = "3";
        break;
    case 4:
        R = "4";
        break;
    case 5:
        R = "5";
        break;
    case 6:
        R = "6";
        break;
    case 7:
        R = "7";
        break;
    case 8:
        R = "8";
        break;
    case 9:
        R = "9";
        break;
    case 10:
        R = "10";
        break;
    case 11:
        R = "J";
        break;
    case 12:
        R = "Q";
        break;
    case 13:
        R = "K";
        break;
    }
    char T = 0;
    switch (this->currType)
    {
    case CLUBS:
        T = 'C';
        break;
    case DIAMONDS:
        T = 'D';
        break;
    case HEARTS:
        T = 'H';
        break;
    case SPADES:
        T = 'S';
        break;
    }

    cout << R << T << "  " << ends;
}

void Hand::add(Card pCard)
{
    currCards.push_back(pCard);
}

void Hand::clear()
{
    currCards.clear();
}

// This helper method display all the cards on a hand
void Hand::getCards()
{
    for (Card c : currCards)
        c.displayCard();
}

int Hand::getTotal() const
{
    int sum = 0;
    int Ace = 0;
    for (Card c : currCards)
    {
        if (c.getValue() != 1)
        {
            sum += c.getValue();
        }
        else
            Ace++;
    }
    for (; Ace > 0; Ace--)
    {
        if (21 > sum + 11)
            sum += 11;
        else
            sum += 1;
    }
    return sum;
}

void Deck::Populate()
{
    currCards.clear();
    int aRank, aType;
    for (aRank = ACE; aRank <= KING; aRank++)
    {
        for (aType = CLUBS; aType <= SPADES; aType++)
        {
            Card card = Card(Rank(aRank), Type(aType));
            currCards.push_back(card);
        }
    }
}
void Deck::shuffle()
{
    random_shuffle(currCards.begin(), currCards.end());
}

Card Deck::deal()
{
    Card card = currCards.back();
    currCards.pop_back();
    return card;
}

bool AbstractPlayer::isBusted()
{
    return this->getTotal() > 21;
}

bool HumanPlayer::isDrawing() const
{
    cout << "Do you want to draw? (y/n):";
    char answer;
    cin >> answer;
    bool drawAgain = (answer == 'y');
    return drawAgain;
}

void HumanPlayer::announce(ComputerPlayer p)
{
    if (this->isBusted())
    {
        cout << "Player busts." << endl;
        cout << "Casino wins." << endl;
    }
    else if (p.isBusted())
    {
        cout << "Casino busts." << endl;
        cout << "Player wins." << endl;
    }

    //If no one busts, check the total scores

    else if (this->getTotal() == p.getTotal())
    {
        cout << "Push: No one wins." << endl;
    }
    else if (this->getTotal() > p.getTotal())
    {
        cout << "Player wins." << endl;
    }
    else if (this->getTotal() < p.getTotal())
    {
        cout << "Casino wins." << endl;
    }
}

bool ComputerPlayer::isDrawing() const
{
    return this->getTotal() <= 16;
}

void BlackJackGame::play()
{
    HumanPlayer human;
    bool isDrawing;

    //Populate and shuffle the deck.
    m_deck.Populate();
    m_deck.shuffle();

    //Clear the casino and human's hand
    m_casino.clear();
    human.clear();

    //deal two cards to human and one card to casino
    m_casino.add(m_deck.deal());
    human.add(m_deck.deal());
    human.add(m_deck.deal());

    //Show the scores obtained by casino and human
    std::cout << "Casino: ";
    m_casino.getCards();
    std::cout << "[" << m_casino.getTotal() << "]" << std::endl;
    std::cout << "Player: ";
    human.getCards();
    std::cout << "[" << human.getTotal() << "]" << std::endl;
    isDrawing = human.isDrawing();

    //When the plauer begins to draw
    while (isDrawing)
    {
        human.add(m_deck.deal());
        std::cout << "Player: ";
        human.getCards();
        std::cout << "[" << human.getTotal() << "]" << std::endl;

        //check if human bursts
        if (human.isBusted())
        {
            std::cout << "Player busts" << std::endl
                      << "Casino wins" << std::endl;
            return;
        }
        isDrawing = human.isDrawing();
    }
    isDrawing = m_casino.isDrawing();

    //When casino begins to draw
    while (isDrawing)
    {
        m_casino.add(m_deck.deal());
        std::cout << "Casino: ";
        m_casino.getCards();
        std::cout << "[" << m_casino.getTotal() << "]" << std::endl;

        //Check if the casino busts
        if (m_casino.isBusted())
        {
            std::cout << "Player wins" << std::endl
                      << "Casino busts" << std::endl;
            return;
        }
        isDrawing = m_casino.isDrawing();
    }
    human.announce(m_casino);
}