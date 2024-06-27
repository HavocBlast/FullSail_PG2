#include "Player.h"

bool Player::HasCards()
{
    if(pile.empty())
    {
        return false;
    }
    return true;
}

void Player::PushCard(Card card)
{
    pile.push_back(card);
}

Card Player::PopCard()
{ 
    Card removedCard = pile.back();
    pile.pop_back();
    return removedCard;
}

void Player::WonCards(std::vector<Card> cards)
{
    for(Card card : cards){
        won.push_back(card);
        score ++;
    }  
}
