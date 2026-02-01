#include <iostream>
#include <vector>
#include <string>
#include "SocialNetworkAnalyzer.h"

// Helper function to print a separator line
void printSeparator() {
    std::cout << "------------------------------------------------------" << std::endl;
}

// Function to run a set of tests on a specific file
void testFile(const std::string& filename) {
    printSeparator();
    std::cout << "Testing file: " << filename << std::endl;

    try {
        // 1. Attempt to load the graph (Constructor)
        SocialNetworkAnalyzer analyzer(filename);
        std::cout << "[V] Graph loaded successfully." << std::endl;

        // Select users for testing from the files (based on social_network_full.txt data)
        // User 1: Kevin_King
        // User 16: Jessica_Williams
        // User 71: Justin_Harris (Mutual friend of both)

        int userA = 1;   // Kevin King
        int userB = 16;  // Jessica Williams

        // 2. Test mutualFriendsCount
        std::cout << "\n--- Testing mutualFriendsCount ---" << std::endl;
        int mutual = analyzer.mutualFriendsCount(userA, userB);
        std::cout << "Mutual friends between " << userA << " and " << userB << ": " << mutual << std::endl;
        // Expected to be at least 1 (User 71 is a mutual friend according to the file edges)

        // Check with the user themselves (should be 0)
        std::cout << "Mutual friends with self (" << userA << ", " << userA << "): "
            << analyzer.mutualFriendsCount(userA, userA) << std::endl;


        // 3. Test suggestNewFriends
        std::cout << "\n--- Testing suggestNewFriends ---" << std::endl;
        int k = 1; // Looking for people with at least one mutual friend
        std::cout << "Requesting suggestions for user " << userA << " with k=" << k << "..." << std::endl;

        std::list<int> suggestions = analyzer.suggestNewFriends(userA, k);

        std::cout << "Suggestions found: ";
        if (suggestions.empty()) {
            std::cout << "None";
        }
        else {
            for (int id : suggestions) {
                std::cout << id << " ";
            }
        }
        std::cout << std::endl;


        // 4. Test mostRemoteUser
        std::cout << "\n--- Testing mostRemoteUser ---" << std::endl;
        int remoteUser = analyzer.mostRemoteUser(userA);
        std::cout << "Most remote user from " << userA << " is: " << remoteUser << std::endl;

    }
    catch (const std::exception& e) {
        // Catch errors (e.g., for AcademicGraph files that do not match the format)
        std::cout << "[X] Failed to process file: " << e.what() << std::endl;
    }
}

int main() {
    // List of all uploaded files to test
    std::vector<std::string> files = {
        "social_network_full.txt",             // Valid format
        "social_network_full_no_bridge.txt",   // Valid format
        "AcademicGraph.txt",                   // Invalid format (will fail loading)
        "AcademicGraph_with_cycle.txt",        // Invalid format (will fail loading)
        "AcademicGraphNoEdges.txt"             // Invalid format (will fail loading)
    };

    std::cout << "Starting SocialNetworkAnalyzer Tests..." << std::endl;

    for (const auto& file : files) {
        testFile(file);
    }

    printSeparator();
    std::cout << "All tests completed." << std::endl;

    return 0;
}