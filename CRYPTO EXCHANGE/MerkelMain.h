#pragma once
using namespace::std;
#include <vector>
#include <iostream>
#include "OrderBookEntry.h"
#include <fstream>
#include "CSVReader.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
public:
	MerkelMain();
	/*** Call this to start the sim */
	void init();
private:
	void printMenu();
	void printHelp();
	void printMarketStats();
	void placeOffer();
	void placeBid();
	void showWallet();
	void gotoNextTimeFrame();
	int getUserOption();
	void enterAsk();
	void enterBid();
	void processUserOptions(int userOption);
	string currentTime;
	OrderBook orderBook{"C:\\Users\\kaelo\\Downloads\\testData.txt"};
	Wallet wallet;
};

