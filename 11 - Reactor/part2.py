import sys
from functools import cache

class Solution():

    def __init__(self):
        self.graph = {}
        self.dfs_calls = 0

    def read(self):
        lines = [line.strip() for line in sys.stdin.readlines()]
        for line in lines:
            node, *neighbours = line.split()
            self.graph[node[:-1]] = neighbours

    @cache
    def dfs(self, start, end):
        self.dfs_calls += 1
        if start == end:
            return 1
        if start not in self.graph:
            return 0
        return sum(self.dfs(next, end) for next in self.graph[start])

if __name__ == "__main__":
    sol = Solution()
    sol.read()
    result =\
        sol.dfs("svr", "fft") * sol.dfs("fft", "dac") * sol.dfs("dac", "out") +\
        sol.dfs("svr", "dac") * sol.dfs("dac", "fft") * sol.dfs("fft", "out")
    print(sol.dfs_calls)
    print(result)
