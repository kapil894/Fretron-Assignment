#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 

struct Person {
    std::string name;
    int paid_amount;
    std::vector<int> apple;
    int total_weight() const {
        return std::accumulate(apple.begin(), apple.end(), 0);
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
        people[0].apple.push_back(weight);
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
        total_amount_paid += person.paid_amount;
    }

    // Calculate the target weight for each person
    int total_weight = 0;
    for (Person& person : people) {
        person.target_weight = (person.paid_amount * 1000) / total_amount_paid; 
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
        for (size_t i = 0; i < person.apple.size(); ++i) {
            std::cout << person.apple[i];
            if (i < person.apple.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " (total " << person.total_weight() << "g)\n";
    }

    return 0;
}
