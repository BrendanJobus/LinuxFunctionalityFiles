def mergesLists(a, b, limit):
    if limit < 0:
        return [], -1

    aIndex, bIndex = 0, 0
    mergedList = []

    elementRange = range(0, limit)

    for _ in elementRange:
        if aIndex < len(a) and bIndex < len(b):
            if a[aIndex] < b[bIndex]:
                mergedList.append(a[aIndex])
                aIndex = aIndex + 1
            elif b[bIndex] < a[aIndex]:
                mergedList.append(b[bIndex])
                bIndex = bIndex + 1
            else:
                break
        elif aIndex >= len(a) and bIndex < len(b):
            mergedList.append(b[bIndex])
            bIndex = bIndex + 1
        elif bIndex >= len(b) and aIndex < len(a):
            mergedList.append(a[aIndex])
            aIndex = aIndex + 1
        else:
            break

    return mergedList, 0

    # a= [1, 3, 10]
    # b= [2,5,8,9]

a = [2,4,6]
b = [3,7,9,10]
limit = -1

print(mergesLists(a,b,limit))