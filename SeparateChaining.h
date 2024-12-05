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

        friend bool operator==(const pair& left, const pair& right) {
            return left.key == right.key;
        }
    };
    vector<list<pair>> table;
    unsigned long totalCollisions = 0;

    unsigned long hornerHash(const string& key) const {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    int nextPrime(int n) const {
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

public:
    SeparateChaining(unsigned long tableSize) {
        table.resize(nextPrime(tableSize));
    }

    bool insert(const string& key, const Keyable& item) {
        unsigned long index = hornerHash(key);
        list<pair>& chain = table[index];

        // Count a collision if the list already has elements
        if (!chain.empty()) {
            ++totalCollisions;  // A collision occurred when inserting into a non-empty chain
            cout << "Collision at index " << index << " with key: " << key << endl;  // Debugging print for collisions
        }

        // Check if the key already exists in the chain to avoid duplicates
        for (const pair& p : chain) {
            if (p.key == key) {
                return false;  // Key already exists, no need to insert again
            }
        }

        // Insert the new key-value pair into the chain
        chain.push_back({key, item});
        return true;
    }



    optional<Keyable> find(const string& key) const {
        unsigned long index = hornerHash(key);
        for (const pair& p : table[index]) {
            if (p.key == key) {
                return p.value;
            }
        }
        return nullopt;
    }

    bool remove(const string& key) {
        unsigned long index = hornerHash(key);
        list<pair>& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }

    void printTable() const {
        cout << "Hash Table (Separate Chaining):" << endl;
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            for (const pair& p : table[i]) {
                cout << "(" << p.key << ", " << p.value << ") ";
            }
            cout << endl;
        }
        cout << "Total Collisions: " << totalCollisions << endl;
    }

    unsigned long getTotalCollisions() const {
        return totalCollisions;
    }
};

#endif // HASHING_SEPARATECHAINING_H
