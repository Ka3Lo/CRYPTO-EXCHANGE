#pragma once
#include <iostream>
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace::std;
class Wallet
{
public:
	Wallet();
	void insertCurrency(string type, double amount);
	bool removeCurrency(string type, double amount);
	bool containsCurrency(string type, double amount);
	bool canFulfillOrder(OrderBookEntry order);
	void processSale(OrderBookEntry& sale);
	string toString();

private:
	map<string, double> currencies;
};

