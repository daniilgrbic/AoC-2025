#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::string line;

    std::cin >> line;
    int sPos = line.find('S');

    std::map<int, int64_t> beams = { { sPos, 1 } };

    while (std::cin >> line)
    {
        std::map<int, int64_t> newBeams;

        for (auto [beam, count] : beams)
        {
            if (line[beam] == '^')
            {
                newBeams[beam - 1] += count;
                newBeams[beam + 1] += count;
            }
            else
            {
                newBeams[beam] += count;
            }
        }

        beams.swap(newBeams);
    }

    int64_t result = 0;
    for (auto [beam, count] : beams)
    {
        result += count;
    }
    std::cout << result << std::endl;

    return 0;
}
