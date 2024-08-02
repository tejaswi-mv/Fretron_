#include <iostream>
#include <vector>
#include <algorithm>

void printDistribution(const std::vector<int>& apples, const std::vector<int>& distribution) {
    std::vector<int> ram, sham, rahim;
    for (size_t i = 0; i < distribution.size(); ++i) {
        if (distribution[i] == 0) ram.push_back(apples[i]);
        else if (distribution[i] == 1) sham.push_back(apples[i]);
        else if (distribution[i] == 2) rahim.push_back(apples[i]);
    }

    std::cout << "Ram: ";
    for (int apple : ram) std::cout << apple << " ";
    std::cout << "\nSham: ";
    for (int apple : sham) std::cout << apple << " ";
    std::cout << "\nRahim: ";
    for (int apple : rahim) std::cout << apple << " ";
    std::cout << std::endl;
}

bool distributeApples(const std::vector<int>& apples, size_t index, int ramTarget, int shamTarget, int rahimTarget, std::vector<int>& distribution, std::vector<int>& currentSums) {
    if (index == apples.size()) {
        return currentSums[0] == ramTarget && currentSums[1] == shamTarget && currentSums[2] == rahimTarget;
    }

    for (int person = 0; person < 3; ++person) {
        int target = (person == 0) ? ramTarget : (person == 1) ? shamTarget : rahimTarget;
        if (currentSums[person] + apples[index] <= target) {
            distribution[index] = person;
            currentSums[person] += apples[index];
            if (distributeApples(apples, index + 1, ramTarget, shamTarget, rahimTarget, distribution, currentSums)) {
                return true;
            }
            currentSums[person] -= apples[index];
        }
    }

    distribution[index] = -1;
    return false;
}

int main() {
    std::vector<int> apples;
    int totalWeight = 0;
    int weight;

    std::cout << "Enter apple weight in grams (-1 to stop): ";
    while (std::cin >> weight && weight != -1) {
        apples.push_back(weight);
        totalWeight += weight;
    }

    std::sort(apples.rbegin(), apples.rend());

    int ramTarget = static_cast<int>(totalWeight * 0.5);
    int shamTarget = static_cast<int>(totalWeight * 0.3);
    int rahimTarget = totalWeight - ramTarget - shamTarget;

    std::vector<int> distribution(apples.size(), -1);
    std::vector<int> currentSums(3, 0);

    if (distributeApples(apples, 0, ramTarget, shamTarget, rahimTarget, distribution, currentSums)) {
        std::cout << "Distribution Result:\n";
        printDistribution(apples, distribution);
    } else {
        std::cout << "Perfect distribution not possible.\n";
        std::cout << "Remaining apples: ";
        for (int apple : apples) {
            std::cout << apple << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
