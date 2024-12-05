#ifndef HASHING_OPENADDRESSING_H
#define HASHING_OPENADDRESSING_H

#include <iostream>
#include <optional>
#include <string>
#include <vector>

using std::cout, std::endl, std::nullopt, std::optional, std::string, std::vector;

template<typename Keyable>
class QuadraticProbing {
private:
    enum State { EMPTY, FILLED, REMOVED };

    struct Hashable {
        string key;
        Keyable value;
        State status = EMPTY;
    };

    vector<Hashable> table;
    unsigned long numItems = 0;
    unsigned long totalCollisions = 0;  // Tracks collisions across the entire table

    // Hash function: Horner's method to compute hash value
    unsigned long hornerHash(const string& key) const {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    // Get next prime number larger than the current value to resize the table
    int nextPrime(int n) {
        if (n % 2 == 0) ++n;
        while (true) {
            bool isPrime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n;
            n += 2;
        }
    }

    // Rehashes the table when the load factor exceeds a threshold
    void rehash() {
        vector<Hashable> oldTable = table;
        table.clear();
        numItems = 0;
        table.resize(nextPrime(oldTable.size() * 2));  // Resize to next prime size

        // Rehash existing entries into the new table
        for (const auto& item : oldTable) {
            if (item.status == FILLED) {
                insert(item.key, item.value);  // Re-insert values from the old table
            }
        }
    }

public:
    // Constructor to initialize table size
    QuadraticProbing(unsigned long tableSize) {
        table.resize(nextPrime(tableSize));
    }

    // Insert a key-value pair into the table
    void insert(const string& key, const Keyable& value) {
        unsigned long index = hornerHash(key);
        unsigned long step = 1;

        // Check if the slot is already filled and count collisions
        while (table[index].status == FILLED) {
            ++totalCollisions;  // Increment collision count
            cout << "Collision at index " << index << " with key: " << key << endl;  // Debug print for collisions
            index = (index + step * step) % table.size();  // Quadratic probing step
            ++step;
        }

        // Insert the key-value pair at the found empty slot
        table[index].key = key;
        table[index].value = value;
        table[index].status = FILLED;  // Mark slot as filled
        ++numItems;

        // If load factor exceeds 50%, rehash the table
        if (numItems > table.size() / 2) {
            cout << "Rehashing triggered" << endl;  // Debugging print for rehash
            rehash();
        }
    }

    // Find the value associated with the given key
    optional<Keyable> find(const string& key) const {
        unsigned long index = hornerHash(key);
        unsigned long step = 1;

        // Probe until the key is found or an empty slot is reached
        while (table[index].status != EMPTY) {
            if (table[index].status == FILLED && table[index].key == key) {
                return table[index].value;
            }
            index = (index + step * step) % table.size();
            ++step;
        }
        return nullopt;  // Return null if the key is not found
    }

    // Remove the key-value pair for the given key
    bool remove(const string& key) {
        unsigned long index = hornerHash(key);
        unsigned long step = 1;

        // Probe until the key is found or an empty slot is reached
        while (table[index].status != EMPTY) {
            if (table[index].status == FILLED && table[index].key == key) {
                table[index].key.clear();
                table[index].value = Keyable();
                table[index].status = REMOVED;
                return true;
            }
            index = (index + step * step) % table.size();
            ++step;
        }
        return false;  // Return false if the key was not found
    }

    // Print the table contents
    void printTable() const {
        cout << "Hash Table (Quadratic Probing):" << endl;
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            if (table[i].status == FILLED) {
                cout << table[i].value;
            } else if (table[i].status == REMOVED) {
                cout << "X";  // Mark removed slots with "X"
            }
            cout << endl;
        }
        cout << "Total Collisions: " << totalCollisions << endl;  // Print total collisions
    }

    // Getter for total collisions
    unsigned long getTotalCollisions() const {
        return totalCollisions;
    }

    // Getter for table size
    unsigned long getTableSize() const {
        return table.size();
    }
};

#endif
