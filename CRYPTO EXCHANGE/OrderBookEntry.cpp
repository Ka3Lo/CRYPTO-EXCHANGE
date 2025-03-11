#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double price, double amount, string Timestamp, string product, OrderBookType orderType, string username)
{
	this->price = price;
	this->amount = amount;
	this->Timestamp = Timestamp;
	this->product = product;
	this->orderType = orderType;
	this->username = username;
}

OrderBookType OrderBookEntry::stringToOrderBookType(string s)
{
	if (s == "ask")
	{
		return OrderBookType::ask;
	}
	if(s == "bid")
	{
		return OrderBookType::bid;
	}
}

bool OrderBookEntry::compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
	return e1.Timestamp < e2.Timestamp;
}

bool OrderBookEntry::compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
	return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
	return e1.price > e2.price;
}
