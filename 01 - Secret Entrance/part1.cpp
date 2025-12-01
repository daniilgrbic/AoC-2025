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

        dial = (dial + direction * clicks) % 100;

        if (dial == 0)
        {
            password += 1;
        }
    }

    std::cout << password << std::endl;

    return 0;
}