#!/usr/bin/python3

size = 10


def insert_l(db, book):
    if isfull(db):
        print("\ndb Full")
        return
    pos = book[0] % size
    if db[pos] is None:
        db[pos] = book
    else:
        i = pos + 1
        while i < size:
            if i == pos:
                break
            elif db[i] is None:
                db[i] = book
                break
            elif i == 9:
                i = 0
            i += 1


def insert_q(db, book):
    if isfull(db):
        print("db full")
        return
    pos = book[0] % 10
    if db[pos] is not None:
        i = 1
        while i < 5:
            pos1 = (pos + (i * i)) % 10
            if db[pos1] is None:
                db[pos1] = book
                break
            i += 1
    else:
        db[pos] = book


def search_l(db, key):
    pos = key % 10
    count = 0
    if db[pos] is not None and db[pos][0] == key:
        count += 1
        print(db[pos])
        print(f"Element found in {count} comparisons")
    else:
        i = pos + 1
        while i < 10:
            count += 1
            if db[i] is not None and db[i][0] == key:
                count += 1
                print(db[i])
                print(f"Element found in {count} comparisons")
                break
            if i == pos:
                print("Element not found")
                break
            if i == 9:
                i = 0
            i += 1


def search_q(db, key):
    pos = key % 10
    count = 0
    if db[pos] is not None and db[pos][0] == key:
        count += 1
        print(db[pos])
        print(f"Element found in {count} comparisons")
    else:
        i = 1
        while i < 5:
            count += 1
            pos1 = (pos + (i * i)) % 10
            if db[pos1] is not None:
                print("Element not found")
                break
            if db[pos1][0] == key:
                print(db[pos1])
                print(f"Element found in {count} comparisons")
                break
            i += 1


def isfull(db):
    for i in range(len(db)):
        if db[i] is None:
            return False
    return True


def main():
    dbl = [None] * size
    dbq = [None] * size

    while True:
        print("\n1.Insert")
        print("\n2.Display data")
        print("\n3.Search")
        print("\n4.Exit")
        ch = int(input("\nChoice:"))
        if ch == 1:
            for i in range(size):
                record = []
                cid = int(input("Enter client id:"))
                cname = input(f"Enter name of {cid}:")
                cpn = int(input(f"Enter phone of {cid}:"))
                record.append(cid)
                record.append(cname)
                record.append(cpn)
                insert_l(dbl, record)
                insert_q(dbq, record)
        elif ch == 2:
            print(dbl)
            print(dbq)
        elif ch == 3:
            s = int(input("Enter the number you want to search:"))
            print("Linear search")
            search_l(dbl, s)
            print("Quadratic Search")
            search_q(dbq, s)
        elif ch == 4:
            break
        else:
            print("\nNot valid choice")


main()
