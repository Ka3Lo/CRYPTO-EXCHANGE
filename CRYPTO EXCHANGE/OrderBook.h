#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

using namespace::std;
class OrderBook
{
public:
	/** construct, reading a csv data file*/
	OrderBook(string filename);
	/**return a vector of all known products in a dataset*/
	vector<string> getKnownProducts();
	/**return vector of Orders according to the sent filters*/
	vector<OrderBookEntry> getOrders(OrderBookType type, string product, string timestamp);
	/** returns the earliest time in the orderbook*/
	string getEarliestTime();
	string getNextTime(string timestamp);
	void insertOrder(OrderBookEntry& order);
	vector<OrderBookEntry> matcheAsksToBids(string products, string timestamp);
	static double computeHighPrice(vector<OrderBookEntry>& orders);
	static double computeLowPrice(std::vector<OrderBookEntry>& orders);
	static double computeAveragePrice(std::vector<OrderBookEntry>& entries);
	static double computePriceSpread(std::vector<OrderBookEntry>& entries);

private:
	vector<OrderBookEntry> orders;

};

