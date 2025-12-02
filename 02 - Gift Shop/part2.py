def main():
    records = input().split(',')
    found = set()
    for record in records:
        start, end = record.split('-')
        base = 1
        while len(str(base)) * 2 <= len(end):
            for reps in range(2, len(end) + 1):
                number = str(base) * reps
                if number in found:
                    continue
                if int(start) <= int(number) <= int(end):
                    print(f"Found {number} in range [{start}, {end}]")
                    found.add(int(number))
            base += 1
    print(sum(found))

if __name__ == "__main__":
    main()
