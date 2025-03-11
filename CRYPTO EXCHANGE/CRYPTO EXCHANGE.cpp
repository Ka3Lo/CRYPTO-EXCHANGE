// CRYPTO EXCHANGE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include <fstream>
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"
using namespace::std;


int main()
{
    Wallet wallet{};
    try
    {     
        wallet.insertCurrency("BTC", 243.22);
        wallet.insertCurrency("ETH", 337.44);
        wallet.insertCurrency("DOGE", -1.1);
        
    }
    catch (const std::exception&)
    {
        cout << "Amount less than 0 was added proceed with caution" << endl;
    }

    cout << "Wallet contents " << wallet.toString() << endl;
    cout << "******************************************************************" << endl;
    cout << endl;
    cout << "After removal wallet contains " << endl;
    wallet.removeCurrency("BTC", 25.33);
    wallet.removeCurrency("ETH", 25.77);
    wallet.removeCurrency("GBP", 0.23);
    cout << "Wallet contents " << wallet.toString() << endl;

    cout << "******************************************************************" << endl;
    cout << endl;

    wallet.containsCurrency("BTC", 217.39);
    wallet.containsCurrency("GBP", 200);
    
}
