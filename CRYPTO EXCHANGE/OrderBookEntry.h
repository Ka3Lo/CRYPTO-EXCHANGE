#pragma once
#include <string>
#include "OrderBookType.h"
#include <algorithm>
using namespace::std;

class OrderBookEntry
{
public:
	double price;
	double amount;
	string Timestamp;
	string product;
	OrderBookType orderType;
	string username;
	OrderBookEntry(double price, double amount, string Timestamp, string product,OrderBookType orderType, string username = "dataset");
	static OrderBookType stringToOrderBookType(string s);
	static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2);
	static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2);
	static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2);
};

