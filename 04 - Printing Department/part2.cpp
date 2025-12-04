#include <iostream>
#include <vector>

std::vector<std::string> readGrid()
{
    std::vector<std::string> grid;
    std::string line;
    int width = 0, height = 0;

    grid.push_back("");
    while (std::cin >> line)
    {
        grid.push_back("." + line + ".");
        width = line.size();
        height += 1;
    }
    grid.push_back("");

    grid.front() = std::string(width + 2, '.');
    grid.back() = std::string(width + 2, '.');

    return grid;
}

int countAdjacent(std::vector<std::string> &grid, int row, int column)
{
    int adjacentScrolls = -1;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (grid[row + i][column + j] == '@')
            {
                adjacentScrolls += 1;
            }
        }
    }

    return adjacentScrolls;
}

int removeScrollsPass(std::vector<std::string> &grid)
{
    int columns = grid[0].size() - 2;
    int rows = grid.size() - 2;

    int removedScrolls = 0;

    for (int row = 1; row <= rows; row++)
    {
        for (int column = 1; column <= columns; column++)
        {
            if (grid[row][column] == '@' && countAdjacent(grid, row, column) < 4)
            {
                grid[row][column] = '.';
                removedScrolls += 1;
            }
        }
    }

    return removedScrolls;
}

int main()
{
    int removedScrolls = 0, rm = -1;
    auto grid = readGrid();

    while(rm)
    {
        rm = removeScrollsPass(grid);
        removedScrolls += rm;
    }

    std::cout << removedScrolls << std::endl;

    return 0;
}