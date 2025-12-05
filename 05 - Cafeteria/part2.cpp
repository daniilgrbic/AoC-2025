#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main()
{
    int64_t from, to;
    char dash;
    std::map<int64_t, int> points;
    while (std::cin >> from >> dash >> to)
    {
        points[from] += 1;
        points[to] -= 1;

        // Drop newline, break if next lines is empty
        std::cin.get();
        if (std::cin.peek() == 10) break;
    }

    int64_t freshIds = 0, current = 0, rangeStart;
    for (auto [point, change] : points)
    {
        if (current == 0)
        {
            rangeStart = point;
        }

        current += change;
        
        if (current == 0)
        {
            freshIds += point - rangeStart + 1;
        }
    }

    std::cout << freshIds << std::endl;
    return 0;
}