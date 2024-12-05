#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>
#include "SeparateChaining.h"   // Include the SeparateChaining class header
#include "OpenAddressing.h"     // Include the OpenAddressing classes header

using namespace std;

class Movie {
public:
    string title;
    string certificate;
    int duration;
    string genre;
    double rating;

    Movie() : title(""), certificate(""), duration(0), genre(""), rating(0.0) {}

    Movie(string title, string certificate, int duration, string genre, double rating)
        : title(title), certificate(certificate), duration(duration), genre(genre), rating(rating) {}

    friend ostream& operator<<(ostream& os, const Movie& movie) {
        os << "Title: " << movie.title << ", Genre: " << movie.genre << ", Rating: " << movie.rating;
        return os;
    }
};

// Function to split a CSV line into fields
vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (char ch : line) {
        if (ch == '\"') {
            inQuotes = !inQuotes;  // Toggle in/out of quotes
        } else if (ch == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += ch;
        }
    }

    if (!field.empty()) {
        fields.push_back(field);  // Add the last field
    }

    return fields;
}

// Function to clean up and convert duration to an integer
int parseDuration(const string& durationStr) {
    string cleaned = durationStr;
    // Remove any non-digit characters
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), [](char c) { return !isdigit(c); }), cleaned.end());

    try {
        if (cleaned.empty()) {
            return 0;  // Return 0 if the duration field is invalid or empty
        }
        return stoi(cleaned);  // Convert to integer
    } catch (const exception& e) {
        cerr << "Error parsing duration: '" << durationStr << "'\nReason: " << e.what() << endl;
        return 0;  // Return 0 if parsing fails
    }
}

// Function to convert rating to a double
double parseRating(const string& ratingStr) {
    try {
        // Handle cases like "Not Rated", "N/A", or missing values
        if (ratingStr == "Not Rated" || ratingStr == "N/A" || ratingStr.empty()) {
            return 0.0;
        }

        // Check if the rating contains non-numeric characters (e.g., genres) and return 0.0 if so
        size_t found = ratingStr.find_first_not_of("0123456789.");
        if (found != string::npos) {
            return 0.0; // Non-numeric characters found, return 0.0
        }

        return stod(ratingStr);  // Convert to double
    } catch (const exception& e) {
        cerr << "Error parsing rating: '" << ratingStr << "'\nReason: " << e.what() << endl;
        return 0.0;  // Return 0.0 if parsing fails
    }
}

// Function to load movies from CSV file
vector<Movie> loadMovies(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        perror("File open error");
        return movies;
    }

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line)) {
        vector<string> fields = parseCSVLine(line);

        // Ensure there are enough fields
        if (fields.size() < 5) {
            cerr << "Skipping line (not enough fields): " << line << endl;
            continue;
        }

        try {
            string title = fields[0];
            string certificate = fields[1];
            int duration = parseDuration(fields[2]);  // Convert duration
            string genre = fields[3];
            double rating = parseRating(fields[4]); // Convert rating

            movies.push_back(Movie(title, certificate, duration, genre, rating));
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument while parsing line: " << line << endl;
            cerr << "Reason: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Out of range error while parsing line: " << line << endl;
            cerr << "Reason: " << e.what() << endl;
        }
    }

    return movies;
}

// Global key functions
string getKeyFunction1(const Movie& movie) {
    return movie.title + "_" + movie.genre.substr(0, 1);  // Concatenate title and first letter of genre
}

string getKeyFunction2(const Movie& movie) {
    stringstream ss;
    ss << movie.title << "_" << movie.rating;  // Concatenate title and rating
    return ss.str();
}

int main() {
    string filename = "movies.csv";
    vector<Movie> movies = loadMovies(filename);

    if (movies.empty()) {
        cout << "No movies found or failed to load movies." << endl;
        return 1;
    }

    // Define the different sizes for hash tables
    vector<int> sizes = {1001, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    // Create Separate Chaining hash tables (half using getKeyFunction1, half using getKeyFunction2)
    vector<SeparateChaining<Movie>> separateChainingTables;
    for (int i = 0; i < 10; ++i) {
        separateChainingTables.push_back(SeparateChaining<Movie>(sizes[i]));
    }

    // Create Open Addressing hash tables (half using getKeyFunction1, half using getKeyFunction2)
    vector<QuadraticProbing<Movie>> openAddressingTables;
    for (int i = 0; i < 10; ++i) {
        openAddressingTables.push_back(QuadraticProbing<Movie>(sizes[i]));
    }

    // Insert movies into Separate Chaining hash tables using two different key functions
    for (int i = 0; i < movies.size(); ++i) {
        string key1 = getKeyFunction1(movies[i]);
        string key2 = getKeyFunction2(movies[i]);

        // Insert into Separate Chaining tables using key1 and key2
        separateChainingTables[i % 10].insert(key1, movies[i]);
        separateChainingTables[5 + (i % 5)].insert(key2, movies[i]);  // Corrected to use 5-9 for the second half
    }

    // Insert movies into Open Addressing hash tables using two different key functions
    for (int i = 0; i < movies.size(); ++i) {
        string key1 = getKeyFunction1(movies[i]);
        string key2 = getKeyFunction2(movies[i]);

        // Insert into Open Addressing tables using key1 and key2
        openAddressingTables[i % 10].insert(key1, movies[i]);
        openAddressingTables[5 + (i % 5)].insert(key2, movies[i]);  // Corrected to use 5-9 for the second half
    }


    // Output the results: collisions and hash table size for open addressing
    ofstream collisionsFile("collisions.txt");

    for (int i = 0; i < 10; ++i) {
        cout << "Separate Chaining Table " << i << " (Collisions: " << separateChainingTables[i].getTotalCollisions() << ")" << endl;
        separateChainingTables[i].printTable();
        collisionsFile << "Separate Chaining Table " << i << ": " << separateChainingTables[i].getTotalCollisions() << " collisions" << endl;
        cout << "----------------------------------------" << endl;
    }

    for (int i = 0; i < 10; ++i) {
        cout << "Open Addressing Table " << i << " (Collisions: " << openAddressingTables[i].getTotalCollisions() << ")" << endl;
        openAddressingTables[i].printTable();
        cout << "Final table size: " << openAddressingTables[i].getTableSize() << endl;
        collisionsFile << "Open Addressing Table " << i << ": " << openAddressingTables[i].getTotalCollisions() << " collisions" << endl;
        collisionsFile << "Final table size: " << openAddressingTables[i].getTableSize() << endl;
        cout << "----------------------------------------" << endl;
    }

    collisionsFile.close();  // Close the file after writing

    return 0;
}
