// orderbook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <cmath>

// Message struct to encapsulate the message fields
struct Message {
public:
	// Variables to hold the fields of input message
	int timestamp;
	char operation;
	int id;
	double price;

	Message(std::string arg);
	~Message();
};

// Orderbook class to manage outstanding entries
class Orderbook {
public:
	std::pair<int,double> highest; // pair to store the highest price of the order book
	std::unordered_map<int, double> ledger;

	Orderbook();
	void handle_message(const Message& message);
	void insert(const int& id, const double& price);
	void erase(const int& id);
	double get_highest_price();
	~Orderbook();
};

// Main function for console application
int main(int argc, char** argv)
{
	// Check command line input
	if (argc == 1) {
		std::cout << "Please input a file to read " << std::endl;
	}

	std::string filename = std::string(argv[1]);

	// Read in file
	std::ifstream input_file(filename);

	//Initialise orderbook object
	Orderbook orderbook;

	if (input_file.is_open()) {

		// Initialise variables
		std::string line;
		int total_time = 0;
		double weighted = 0;
		int last_timestamp = -1; // last_timestamp stored to calculate the timedelta for each step

		// Read the file line by line
		while (std::getline(input_file, line)) {
			
			Message message(line); // Parse the input line into Message fields
			
			// Calculate the weighted average from the previous timestamp to current timestep if not the initial timestamp
			if (last_timestamp > -1) {
				double highest_price = orderbook.get_highest_price();
				int timedelta = message.timestamp - last_timestamp;
				total_time += timedelta;
				if (!isnan(highest_price)) {
					weighted += highest_price * timedelta;
				}
			}

			// After calculating weighted average, pass message onto orderbook to handle the message
			orderbook.handle_message(message);
			
			last_timestamp = message.timestamp;
		}

		// Close file after finished reading
		input_file.close();

		// Print final answer
		std::cout << weighted / double(total_time) << std::endl;
	}
	else {
		std::cout << "Invalid input filename" << std::endl; // Output error message if file cannot be opened
	}

	return 0;

}

// Parse the input line with the constructor and stringstream
Message::Message(std::string arg) :timestamp(-1), operation(), id(-1) {
	std::istringstream istream(arg);
	istream >> this->timestamp >> this->operation >> this->id;
	if (this->operation == 'I') {
		istream >> this->price;
	}
}

Message::~Message() {}

Orderbook::Orderbook() :ledger{}, highest{} {
}

Orderbook::~Orderbook() {
	ledger.clear();
}

void Orderbook::handle_message(const Message& message) {
	// Handle insert/erase operations
	if (message.operation == 'I') {
		this->insert(message.id, message.price);
	}
	else if (message.operation == 'E') {
		this->erase(message.id);
	}
}

void Orderbook::insert(const int& id, const double& price) {
	ledger.try_emplace(id, price);

	// Update the highest price if the new entry is larger than current highest price
	if (price > highest.second) {
		highest = std::make_pair(id, price);
	}
	return;
}

void Orderbook::erase(const int& id) {
	ledger.erase(id);

	// Update hihgest price if entry to be removed was the highest price
	if (id == highest.first) {
		int max_id;
		double max = 0;
		for (auto& it : ledger) {
			if (it.second > max) {
				max_id = it.first;
				max = it.second;
			}
		}
		highest = std::make_pair(max_id, max);
	}
	return;
}

double Orderbook::get_highest_price() {

	// Return nan if orderbook is empty
	if (ledger.empty()) {
		return nan("0");
	}

	// Get the highest outstanding price by iterating through
	return highest.second;
}
