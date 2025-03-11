#include "CSVReader.h"

CSVReader::CSVReader()
{
}

vector<OrderBookEntry> CSVReader::readCSV(string csvFilename)
{
    vector<OrderBookEntry> entries;

    ifstream csvFile{ csvFilename };
    string line;

    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception&)
            {
                //cout << "CSVReader::readCSV read BAD data " << endl;
            }
            
        }

        csvFile.close();
    }

    
    return entries;
}

vector<string> CSVReader::tokenise(string csvLine, char separator)
{
    signed int start, end;
    string token;
    vector<string> tokens;

    start = csvLine.find_first_not_of(separator, 0);

    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;

        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;

    } while (end > 0);
    return tokens;
}

OrderBookEntry CSVReader::stringToOBE(string priceString, string amountString, string timestamp, string product, OrderBookType orderType)
{
    double price, amount;

    try
    {
        price = stod(priceString);
        amount = stod(amountString);
    }
    catch (const std::exception&)
    {
        cout << "CSVReader::stringToOBE Bad float! " << priceString << endl;
        cout << "CSVReader::stringToOBE Bad float! " << amountString << endl;
        throw;
    }

    OrderBookEntry obe
    {
        price,
        amount,
        timestamp,
        product,
        orderType
    };
    return obe;
}

OrderBookEntry CSVReader::stringToOBE(vector<string> tokens)
{
    double price, amount;

    if (tokens.size() != 5)
    {
        //cout << "Bad line!" << endl;
        throw exception{};
    }
    try
    {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }
    catch (const std::exception&)
    {
        cout << "Bad code HERE " << endl;
        throw;
    }
    OrderBookEntry obe
    {
        price,
        amount,
        tokens[0],
        tokens[1],
        OrderBookEntry::stringToOrderBookType(tokens[2])
    };
    return obe;
}
