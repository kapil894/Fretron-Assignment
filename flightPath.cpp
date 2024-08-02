#include <iostream>
#include <vector>
#include <iomanip>

// Define a FlightPath type
typedef std::vector<std::pair<int, int>> FlightPath;

// Function to print the flight paths
void printFlightPaths(const std::vector<FlightPath>& flightPaths) {
    int pathNumber = 1;

    for (const auto& path : flightPaths) {
        std::cout << "Path " << pathNumber++ << std::endl;
        std::cout << "=======" << std::endl;
        
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << (i == 0 ? "Start" : "Move") << " (" 
                      << path[i].first << ", " << path[i].second << ")" << std::endl;
        }
        
        std::cout << "Arrive (" << path.back().first << ", " << path.back().second << ")" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    // Define flight paths
    FlightPath flight1 = { {100, 100}, {200, 200}, {300, 300} };
    FlightPath flight2 = { {100, 100}, {200, 400}, {300, 200} };
    FlightPath flight3 = { {100, 100}, {400, 200}, {300, 400} };

    std::vector<FlightPath> flightPaths = { flight1, flight2, flight3 };

    printFlightPaths(flightPaths);

    return 0;
}
