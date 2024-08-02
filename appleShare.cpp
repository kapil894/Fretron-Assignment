#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Include this header for std::accumulate

struct Person {
    std::string name;
    int amount_paid;
    std::vector<int> apples;
    int total_weight() const {
        return std::accumulate(apples.begin(), apples.end(), 0);
    }
    int target_weight;
};

void distribute_apples(std::vector<int>& apple_weights, std::vector<Person>& people) {
    for (int weight : apple_weights) {
        // Sort people by the difference between target weight and current weight
        std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
            return (a.target_weight - a.total_weight()) > (b.target_weight - b.total_weight());
        });
        // Give the apple to the person with the largest difference
        people[0].apples.push_back(weight);
    }
}

int main() {
    // Define the people and their contributions
    std::vector<Person> people = {
        {"Ram", 50},
        {"Sham", 30},
        {"Rahim", 20}
    };

    // Calculate the total amount paid
    int total_amount_paid = 0;
    for (const Person& person : people) {
        total_amount_paid += person.amount_paid;
    }

    // Calculate the target weight for each person
    int total_weight = 0;
    for (Person& person : people) {
        person.target_weight = (person.amount_paid * 1000) / total_amount_paid; // Assuming 1 unit weight = 1 gram
        total_weight += person.target_weight;
    }

    // Input apple weights
    std::vector<int> apple_weights;
    std::cout << "Enter apple weight in gram (-1 to stop): ";
    while (true) {
        int weight;
        std::cin >> weight;
        if (weight == -1) {
            break;
        }
        apple_weights.push_back(weight);
    }

    // Sort the apple weights in descending order
    std::sort(apple_weights.begin(), apple_weights.end(), std::greater<int>());

    // Distribute the apples
    distribute_apples(apple_weights, people);

    // Output the distribution result
    std::cout << "Distribution Result:\n";
    for (const Person& person : people) {
        std::cout << person.name << ": ";
        for (size_t i = 0; i < person.apples.size(); ++i) {
            std::cout << person.apples[i];
            if (i < person.apples.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " (total " << person.total_weight() << "g)\n";
    }

    return 0;
}
