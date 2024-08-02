#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 10;

// Directions for movement (UP, LEFT, DOWN, RIGHT)
enum Direction { UP, LEFT, DOWN, RIGHT };

// Define a Position type
typedef pair<int, int> Position;

// Define a Path type
typedef vector<Position> Path;

// Function prototypes
bool isValidPosition(const Position& pos);
bool isSoldierAt(const vector<Position>& soldiers, const Position& pos);
vector<Position> getValidSoldierPositions(const vector<Position>& soldiers, const Position& pos);
Direction turnLeft(Direction dir);
bool moveCastle(Position& pos, Direction& dir, vector<Position>& soldiers);
void printPath(const Path& path);
vector<Path> findAllPaths(vector<Position> soldiers, Position startPosition);

int main() {
    int numSoldiers;
    vector<Position> soldiers;

    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;

    soldiers.resize(numSoldiers);

    for (int i = 0; i < numSoldiers; ++i) {
        int x, y;
        cout << "Enter coordinates for soldier " << (i + 1) << " (space-separated): ";
        cin >> x >> y;
        soldiers[i] = make_pair(x, y);
    }

    Position startPosition;
    cout << "Enter the coordinates for your 'special' castle (space-separated): ";
    cin >> startPosition.first >> startPosition.second;

    vector<Path> paths = findAllPaths(soldiers, startPosition);

    cout << "Thanks. There are " << paths.size() << " unique paths for your 'special_castle'" << endl;

    int pathCount = 1;
    for (const Path& path : paths) {
        cout << "Path " << pathCount++ << endl;
        cout << "=======" << endl;
        printPath(path);
        cout << endl;
    }

    return 0;
}

bool isValidPosition(const Position& pos) {
    return pos.first >= 1 && pos.first <= BOARD_SIZE && pos.second >= 1 && pos.second <= BOARD_SIZE;
}

bool isSoldierAt(const vector<Position>& soldiers, const Position& pos) {
    for (const Position& soldier : soldiers) {
        if (soldier == pos) {
            return true;
        }
    }
    return false;
}

vector<Position> getValidSoldierPositions(const vector<Position>& soldiers, const Position& pos) {
    vector<Position> validPositions;

    for (const Position& soldier : soldiers) {
        if (soldier != pos) {
            validPositions.push_back(soldier);
        }
    }

    return validPositions;
}

Direction turnLeft(Direction dir) {
    return static_cast<Direction>((dir + 3) % 4); // Turn left
}

bool moveCastle(Position& pos, Direction& dir, vector<Position>& soldiers) {
    Position nextPos = pos;

    // Move forward based on the direction
    switch (dir) {
        case UP:    nextPos.first--; break;
        case LEFT:  nextPos.second--; break;
        case DOWN:  nextPos.first++; break;
        case RIGHT: nextPos.second++; break;
    }

    // Check if the move is valid
    if (!isValidPosition(nextPos)) {
        return false;
    }

    // Check if there is a soldier at the next position
    if (isSoldierAt(soldiers, nextPos)) {
        // Remove soldier from the list
        soldiers.erase(remove(soldiers.begin(), soldiers.end(), nextPos), soldiers.end());
        pos = nextPos;
        return true;
    }

    return false;
}

void printPath(const Path& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        if (i == 0) {
            cout << "Start (" << path[i].first << ", " << path[i].second << ")" << endl;
        } else if (i == path.size() - 1) {
            cout << "Arrive (" << path[i].first << ", " << path[i].second << ")" << endl;
        } else {
            cout << "Move (" << path[i].first << ", " << path[i].second << ")" << endl;
        }
    }
}

vector<Path> findAllPaths(vector<Position> soldiers, Position startPosition) {
    vector<Path> allPaths;
    queue<pair<Position, Direction>> bfsQueue;
    set<Position> visited;
    
    Direction initialDirection = RIGHT; // Starting direction

    bfsQueue.push(make_pair(startPosition, initialDirection));
    visited.insert(startPosition);

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();

        Position currentPosition = current.first;
        Direction currentDirection = current.second;
        Path currentPath = {currentPosition};

        // Simulate all possible moves
        for (int step = 0; step < 4; ++step) {
            if (moveCastle(currentPosition, currentDirection, soldiers)) {
                // Found a valid move, add to the path and continue
                currentPath.push_back(currentPosition);
                bfsQueue.push(make_pair(currentPosition, turnLeft(currentDirection)));
                visited.insert(currentPosition);
            }
            currentDirection = turnLeft(currentDirection); // Change direction
        }

        // If we are back to the starting position
        if (currentPosition == startPosition) {
            allPaths.push_back(currentPath);
        }
    }

    return allPaths;
}
