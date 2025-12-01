#include <iostream>

int main()
{
    int dial = 50;
    int password = 0;

    std::string rotation;

    while (std::cin >> rotation)
    {
        int direction = (rotation.front() == 'L') ? -1 : 1;
        int clicks = std::stoi(rotation.substr(1));

        // Count full rotations, remaining clicks is now < 100
        password += abs(clicks / 100);
        clicks %= 100;
        if (clicks < 0)
        {
            clicks += 100;
        }

        // Do remaining clicks hit a 0? (do not count if starting from 0)
        int finalPosition = dial + direction * clicks;
        if (dial != 0)
        {
            if (finalPosition >= 100 || finalPosition <= 0)
            {
                password += 1;
            }
        }

        dial = (finalPosition + 100) % 100;
    }

    std::cout << password << std::endl;

    return 0;
}