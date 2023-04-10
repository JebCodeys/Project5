#ifndef HASHING_SEPARATECHAINING_H
#define HASHING_SEPARATECHAINING_H

#include <functional>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>
using std::cout, std::endl, std::function, std::iterator, std::list, std::nullopt, std::optional, std::string, std::vector;

template<typename Keyable>
class SeparateChaining {
private:
    vector<list<Keyable>> table;
    function<string(Keyable)> getKey;

    unsigned long hornerHash(string key) const {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

public:
    // Constructor
    SeparateChaining(unsigned long tableSize, function<string(Keyable)> getKey) {
        // This will fill the table with empty lists
        table.resize(nextPrime(tableSize));
        this->getKey = getKey;
    }

    // Insert
    bool insert(Keyable item) {
        // Get the key from the item
        string key = getKey(item);
        // If the item is already in the table, do not insert it
        if (!find(key)) {
            // Hash the key to get an index
            unsigned long index = hornerHash(key);
            // Put the item at that index in the table
            table[index].push_back(item);
            return true;
        }
        return false;
    }

    // Find
    optional<Keyable> find(string key) const {
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Check each item in the list at the index to see if the key matches
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (getKey(*it) == key) {
                // We found the item
                return *it;
            }
        }
        // We didn't find the item
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Check each item in the list at the index to see if the key matches
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (getKey(*it) == key) {
                // We found the item
                // Remove the item
                table[index].remove(*it);
                return true;
            }
        }
        // We didn't find the item
        return false;
    }

    // Print the table
    void printTable() const {
        cout << "Beginning of table" << endl;
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                if (it == table[i].begin()) {
                    cout << *it;
                } else {
                    cout << ", " << *it;
                }
            }
            cout << endl;
        }
        cout << "End of table" << endl;
    }
};

#endif
