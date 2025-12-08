#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

class DSU
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n)
    {
        parent = std::vector<int>(n);
        rank = std::vector<int>(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find_set(int a) const
    {
        if (a == parent[a])
            return a;
        return find_set(parent[a]);
    }

    int set_rank(int a) const
    {
        a = find_set(a);
        return rank[a];
    }

    void union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            rank[a] += rank[b];
        }
    }
};

int64_t distanceSq(const std::vector<int> &a, const std::vector<int> &b)
{
    int64_t dx = a[0] - b[0];
    int64_t dy = a[1] - b[1];
    int64_t dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}

int main()
{
    std::vector<std::vector<int>> points;
    std::vector<int> point = {0, 0, 0};
    char c;
    while (std::cin >> point[0] >> c >> point[1] >> c >> point[2])
    {
        points.push_back(point);
    }

    DSU dsu(points.size());

    std::vector<std::tuple<int64_t, int, int>> allPairs;
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            int64_t d = distanceSq(points[i], points[j]);
            allPairs.push_back({d, i, j});
        }
    }
    std::sort(allPairs.begin(), allPairs.end());

    for (int iter = 0;; iter++)
    {
        int bestA = std::get<1>(allPairs[iter]);
        int bestB = std::get<2>(allPairs[iter]);

        dsu.union_sets(bestA, bestB);

        int setCount = 0;
        for (int i = 0; i < points.size(); i++)
        {
            if (i == dsu.find_set(i))
            {
                setCount++;
            }
        }

        if (setCount == 1)
        {
            std::cout << "Iter: " << iter + 1 << " Sets: " << setCount << std::endl;
            std::cout << points[bestA][0] * points[bestB][0] << std::endl;
            break;
        }
    }

    return 0;
}
