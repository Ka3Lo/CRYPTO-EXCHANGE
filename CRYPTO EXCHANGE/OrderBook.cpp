#include "OrderBook.h"

OrderBook::OrderBook(string filename)
{
	orders = CSVReader::readCSV(filename); 
}

vector<string> OrderBook::getKnownProducts()
{
	vector<string> products;
	map<string, bool> prodMap;

	for (OrderBookEntry& e : orders)
	{
		prodMap[e.product] = true;
	}

	for (auto const& e : prodMap)
	{
		products.push_back(e.first);
	}
	return products;
}

vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, string product, string timestamp)
{
	vector<OrderBookEntry> entries;

	for (OrderBookEntry& e : orders)
	{
		if (e.orderType == type && e.product == product && e.Timestamp == timestamp)
		{
			entries.push_back(e);
		}
	}
	return entries;
}

string OrderBook::getEarliestTime()
{
	return getNextTime("");
}

string OrderBook::getNextTime(string timestamp)
{
	string next_timestamp = "";
	for (OrderBookEntry& e : orders)
	{
		if (e.Timestamp > timestamp)
		{
			next_timestamp = e.Timestamp;
			break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = orders[0].Timestamp;
	}

	return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order);
	sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

vector<OrderBookEntry> OrderBook::matcheAsksToBids(string products, string timestamp)
{
	vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, products, timestamp);
	vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, products, timestamp);
	vector<OrderBookEntry> sales;
	sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
	sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

	for (OrderBookEntry& ask : asks)
	{
		for (OrderBookEntry& bid : bids)
		{
			if (bid.price >= ask.price)
			{
				OrderBookEntry sale{ ask.price, 0, timestamp, products, OrderBookType::asksale };

				if (bid.username == "Simuser")
				{
					sale.username = "Simuser";
					sale.orderType = OrderBookType::bidsale;
				}
				if (ask.username == "Simuser")
				{
					sale.username = "Simuser";
					sale.orderType = OrderBookType::asksale;
				}
				
				if (bid.amount == ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;
				}
				if (bid.amount > ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = bid.amount - ask.amount;
					break;
				}
				if (bid.amount < ask.amount && bid.amount > 0)
				{
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount = ask.amount - bid.amount;
					bid.amount = 0;
					continue;
				}

			}
		}
	}
	return sales;
}

double OrderBook::computeHighPrice(vector<OrderBookEntry>& orders)
{
	double highest = orders.at(0).price;

	for (OrderBookEntry& entry : orders)
	{
		if (entry.price >= highest)
			highest = entry.price;
		else
			continue;
	}
	return highest;
}

double OrderBook::computeLowPrice(std::vector<OrderBookEntry>& orders)
{
	double lowest = orders.at(0).price;

	for (OrderBookEntry& entry : orders)
	{
		if (entry.price <= lowest)
			lowest = entry.price;
		else
			continue;
	}
	return lowest;
}
/** returns the average price*/
double OrderBook::computeAveragePrice(std::vector<OrderBookEntry>& entries)
{
	double sum = 0.0;
	for (OrderBookEntry& entry : entries)
	{
		sum += entry.price;
	}
	return sum / entries.size();
}

double OrderBook::computePriceSpread(std::vector<OrderBookEntry>& entries)
{
	double lowest = computeLowPrice(entries);
	double highest = computeHighPrice(entries);
	double spread = highest - lowest;
	return spread;
}
