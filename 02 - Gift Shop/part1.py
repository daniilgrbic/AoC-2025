def main():
    result = 0
    records = input().split(',')
    for record in records:
        start, end = record.split('-')
        current = int(start[:max(len(start)//2, 1)])
        while int(str(current) * 2) < int(start):
            current += 1
        while int(str(current) * 2) <= int(end):
            print(f"Found {int(str(current) * 2)} in range [{start}, {end}]")
            result += int(str(current) * 2)
            current += 1
    print(result)

if __name__ == "__main__":
    main()
