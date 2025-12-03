#include <iostream>
#include <vector>

class JoltageOptimizer
{
private:
    int64_t maxJoltage = 0;

    std::vector<int> digitizeBank(std::string &bankStr)
    {
        std::vector<int> bank(bankStr.size());
        for (int i = 0; i < bankStr.size(); i++)
        {
            bank[i] = bankStr[i] - '0';
        }
        return bank;
    }

    void optimizeHelper(std::vector<int> &bank, int pos, int remaining)
    {
        int choiceCount = bank.size() - remaining + 1 - pos;
        auto largestBattery = std::max_element(bank.begin() + pos, bank.begin() + pos + choiceCount);

        maxJoltage = maxJoltage * 10 + *largestBattery;
        remaining -= 1;

        if (remaining)
        {
            optimizeHelper(bank, largestBattery - bank.begin() + 1, remaining);
        }
    }

public:
    int64_t optimize(std::string &bankStr)
    {
        auto bank = digitizeBank(bankStr);
        int bankLength = bank.size();

        maxJoltage = 0;
        optimizeHelper(bank, 0, 12);

        return maxJoltage;
    }
};

int main()
{
    auto jo = JoltageOptimizer();
    int64_t maxJoltage = 0;

    std::string bank;
    while (std::cin >> bank)
    {
        maxJoltage += jo.optimize(bank);
    }

    std::cout << maxJoltage << std::endl;
    return 0;
}