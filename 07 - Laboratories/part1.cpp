#include <iostream>
#include <set>
#include <vector>

int main()
{
    std::string line;

    std::cin >> line;
    int sPos = line.find('S');

    std::vector<std::string> grid = { line };
    while (std::cin >> line)
    {
        grid.push_back(line);
    }

    std::set<int> beams = { sPos };
    int splits = 0;

    for (auto &row : grid)
    {
        std::set<int> newBeams;

        for (auto beam : beams)
        {
            if (row[beam] == '.')
            {
                newBeams.insert(beam);
                row[beam] = '|';
            }
            else if (row[beam] == '^')
            {
                splits++;

                newBeams.insert(beam - 1);
                row[beam - 1] = '|';

                newBeams.insert(beam + 1);
                row[beam + 1] = '|';
            }
            else if (row[beam] == 'S')
            {
                newBeams.insert(beam);
            }
        }

        std::cout << row << std::endl;
        beams.swap(newBeams);
    }

    std::cout << splits << std::endl;
    return 0;
}