from sys import stdin
from z3 import Sum, Int, Optimize, sat

def solve(line: str) -> int:
    line = line.strip()
    _, *buttons, joltage = line.split(" ")
    buttons = [[int(i) for i in b[1:-1].split(",")] for b in buttons]
    joltage = [int(i) for i in joltage[1:-1].split(",")]

    optimizer = Optimize()

    # Variables - press counts for each button
    press_counts = [Int(f"btn_{bid}") for bid in range(len(buttons))]

    # Constraints - number of button presses can't be negative
    for presses in press_counts:
        optimizer.add(presses >= 0)
    
    # Target - button presses should lead to desired joltage state
    for position, value in enumerate(joltage):
        increases = [press_counts[i] for i, btn in enumerate(buttons) if position in btn]
        optimizer.add(Sum(increases) == value)

    optimizer.minimize(Sum(press_counts))
    assert optimizer.check() == sat

    model = optimizer.model()
    return sum(model[presses].as_long() for presses in press_counts)

def main():
    data = stdin.readlines()
    result = 0
    for line in data:
        result += solve(line)
    print(result)

main()
