#include <iostream>

int digit(char d)
{
    return d - '0';
}

int maxJoltageInBank(std::string bank)
{
    int maxJoltage = 0;
    int largestBattery = 0;

    for (char battery : bank)
    {
        maxJoltage = std::max(
            maxJoltage,
            largestBattery * 10 + digit(battery));
        largestBattery = std::max(
            largestBattery,
            digit(battery));
    }

    return maxJoltage;
}

int main()
{
    std::string bank;
    int maxJoltage = 0;

    while (std::cin >> bank)
    {
        maxJoltage += maxJoltageInBank(bank);
    }

    std::cout << maxJoltage << std::endl;
    return 0;
}