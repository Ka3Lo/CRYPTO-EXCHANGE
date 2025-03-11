#pragma once
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace::std;

class CSVReader
{
public:
	CSVReader();
	static vector<OrderBookEntry> readCSV(string csvFilename);
	static vector<string> tokenise(string csvLine, char separator);
	static OrderBookEntry stringToOBE(string priceString, string amountString, string timestamp, string product, OrderBookType orderType);
private:
	static OrderBookEntry stringToOBE(vector<string> tokens);
};

