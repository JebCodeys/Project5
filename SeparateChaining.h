#ifndef HASHING_SEPARATECHAINING_H
#define HASHING_SEPARATECHAINING_H

#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>
using std::cout, std::endl, std::list, std::nullopt, std::optional, std::string, std::vector;

template<typename Keyable>
class SeparateChaining {
private:
    struct pair {
        string key;
        Keyable value;

        // Overload == operator
        friend bool operator == (const pair& left, const pair& right) {
            return left.key == right.key;
        }
    };
    vector<list<pair>> table;

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
    SeparateChaining(unsigned long tableSize) {
        // This will fill the table with empty lists
        table.resize(nextPrime(tableSize));
    }

    // Insert
    bool insert(string key, Keyable item) {
        // If the item is already in the table, do not insert it
        if (!find(key)) {
            // Hash the key to get an index
            unsigned long index = hornerHash(key);
            // Put the item at that index in the table
            table[index].push_back({key, item});
            return true;
        }
        return false;
    }

    // Find
    optional<Keyable> find(string key) const {
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Check each item in the list at the index to see if the key matches
        for (const pair& p : table[index]) {
            if (p.key == key) {
                // We found the item
                return p.value;
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
        for (pair& p : table[index]) {
            if (p.key == key) {
                // We found the item
                // Remove the item
                table[index].remove(p);
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
            for (const pair& p : table[i]) {
                if (p == *table[i].begin()) {
                    cout << p.value;
                } else {
                    cout << ", " << p.value;
                }
            }
            cout << endl;
        }
        cout << "End of table" << endl;
    }
};

#endif
