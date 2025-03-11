#include "MerkelMain.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int option;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);
    while (true)
    {
        printMenu();
        option = getUserOption();

        if (option < 1 || option > 6)
            break;
        else
            processUserOptions(option);
    }

}


void MerkelMain::printMenu()
{
    cout << "1: Print help " << endl;
    cout << "2: Print exchange stats" << endl;
    cout << "3: Make an offer" << endl;
    cout << "4: Make a bid" << endl;
    cout << "5: Print wallet" << endl;
    cout << "6: Continue" << endl;
    cout << "Select an option" << endl;
    cout << "===================================" << endl;
    cout << "Type in 1 - 6" << endl;
    cout << "Current time is: " << currentTime << endl;
}

void MerkelMain::printHelp()
{
    cout << "Help - choose options from the menu" << endl;
    cout << "and follow the on screen instructions." << endl;
}

void MerkelMain::printMarketStats()
{

    for (string const p : orderBook.getKnownProducts())
    {
        cout << "Products: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        cout << "Asks seen: " << entries.size() << endl;
        cout << "Max ask: " << OrderBook::computeHighPrice(entries) << endl;
        cout << "Low ask: " << OrderBook::computeLowPrice(entries) << endl;
        cout << "Average: " << OrderBook::computeAveragePrice(entries) << endl;
        cout << "Price spread: " << OrderBook::computePriceSpread(entries) << endl;
    }
}


void MerkelMain::showWallet()
{
    cout << wallet.toString() << endl;
}

void MerkelMain::gotoNextTimeFrame()
{
    cout << "Going to the next time frame" << endl;
    for (string p : orderBook.getKnownProducts())
    {
        cout << "Matching " << p << endl;
        vector<OrderBookEntry> sales = orderBook.matcheAsksToBids(p, currentTime);
        cout << "Sales: " << sales.size() << endl;
        for (OrderBookEntry& sale : sales)
        {
            cout << "Sale price: " << sale.price << " amount: " << sale.amount << endl;
            if (sale.username == "Simuser")
            {
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption;
    string line;
    cout << "Type in 1-6 to continue: ";
    getline(cin, line);
    try
    {
        userOption = stoi(line);
    }
    catch (const std::exception&)
    {
        cout << "MerkelMain::getUserOption() WARNING" << endl;
    }
    
    cout << "You chose: " << userOption << endl;
    return userOption;
}

void MerkelMain::enterAsk()
{
    cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5: ";
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "Bad input! " << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringToOBE(
                tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            
            obe.username = "Simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good" << endl;
                orderBook.insertOrder(obe);
            }
            else
                cout << "Wallet has insufficient funds" << endl;
            
        }

        catch (const std::exception&)
        {
            cout << " MerkelMain::enterAsk() bad input !" << endl;
        }
        
    }
    cout << "You typed: " << input << endl;
}

void MerkelMain::enterBid()
{
    cout << "Make a bid - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5: ";
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "Bad input! " << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringToOBE(
                tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);

            obe.username = "Simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good" << endl;
                orderBook.insertOrder(obe);
            }
            else
                cout << "Wallet has insufficient funds" << endl;

        }

        catch (const std::exception&)
        {
            cout << " MerkelMain::enterBid() bad input !" << endl;
        }

    }
}

void MerkelMain::processUserOptions(int userOption)
{
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        showWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeFrame();
    }
}

