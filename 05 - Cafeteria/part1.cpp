#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class FreshRanges
{
private:
    std::map<int64_t, int> ranges;

public:
    FreshRanges()
    {
        int64_t from, to;
        char dash;
        std::vector<std::pair<int64_t, int>> points;
        while (std::cin >> from >> dash >> to)
        {
            points.push_back({from, +1});
            points.push_back({to, -1});

            // Drop newline, break if next lines is empty
            std::cin.get();
            if (std::cin.peek() == 10) break;
        }
        std::sort(points.begin(), points.end());

        int current = 0;
        for (auto [point, type] : points)
        {
            current += type;
            ranges[point] = current;
        }

        // Base cases
        ranges[0] = 0;
        ranges[INT64_MAX] = 0;
    }

    bool isFresh(int64_t id)
    {
        // Case 0: id is before or after all the rnages -> return false
        if (id < ranges.begin()->first || id > ranges.rbegin()->first)
        {
            return false;
        }

        // Case 1: id is on the edge of a range -> then we awlays return true
        if (ranges.count(id))
        {
            return true;
        }

        std::pair<int64_t, int> search = {id, -1};
        auto nextPoint = std::upper_bound(ranges.begin(), ranges.end(), search);
        auto prevPoint = --nextPoint;

        // Case 2: We need to check number of "open" ranges for the previous point
        return prevPoint->second > 0;
    }
};

int main()
{
    auto ranges = FreshRanges();

    int64_t id;
    int fresh = 0;
    while (std::cin >> id)
    {
        fresh += ranges.isFresh(id);
    }

    std::cout << fresh << std::endl;
    return 0;
}