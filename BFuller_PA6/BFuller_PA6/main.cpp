/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
Author: Blayne Fuller

Term: SPR 26
Course: CptS122
Assignment: PA6, Morse Code / AlphaNumeric Converter

Description: This program uses a binary search tree
to map alphanumeric "keys" to morse code "vals", it 
supports alphanumeric text -> morse conversion, 
utilizing file streams for data storage and input
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#include "BST.hpp"
#include <iostream>
#include <string>

int main(void)
{
    // 1. Test Constructor & File Reading
    // This will trigger your "Temp Debug Code" print statements
    std::cout << "--- Initializing BST (Reading MorseTable.txt) ---" << std::endl;
    BST<char, std::string> morseTree;
    std::cout << "BST Initialized successfully.\n" << std::endl;

    // 2. Test In-Order Print
    // This proves the tree is alphabetically sorted A-Z, 0-9
    std::cout << "--- Testing In-Order Traversal (Should be Alphabetical) ---" << std::endl;
    morseTree.printInOrder();
    std::cout << std::endl;

    // 3. Test Manual Search
    // This proves the search logic finds the correct Morse strings
    std::cout << "--- Testing Individual Searches ---" << std::endl;
    char testChars[] = { 'A', 'M', 'Z', '1', '?' }; // '?' likely doesn't exist

    for (char c : testChars) {
        std::string result = morseTree.search(c);
        if (!result.empty()) {
            std::cout << "Found '" << c << "': " << result << std::endl;
        }
        else {
            std::cout << "'" << c << "' not found in tree." << std::endl;
        }
    }

    // 4. Test Case Sensitivity (Requirement Check)
    // The tree usually stores 'A', so searching for 'a' might fail 
    // unless you use toupper() in your final conversion logic.
    std::cout << "\n--- Testing Case Sensitivity ---" << std::endl;
    std::cout << "Searching for 'a': " << (morseTree.search('a').empty() ? "Not Found" : "Found") << std::endl;

    return 0;
}