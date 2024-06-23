import DynamicArrayProject


def arrayToList(array):
    return [array[i] for i in range(array.size())]


def testAdding(array):
    expect_array = arrayToList(array)
    expect_array.append('last')
    array.push_back('last')
    expect_array.insert(0, 'first')
    array.push_front('first')
    expect_array.insert(3, 'middle')
    array.insert(3, 'middle')
    if expect_array != arrayToList(array):
        return False
    return True


def testClear(array):
    capacity = array.capacity()
    array.clear()
    return arrayToList(array) == [] and array.size() == 0 and array.capacity() == capacity


def testConstructor(array, expect_array, expect_capacity):
    return arrayToList(array) == expect_array and array.capacity() == expect_capacity


def testPointers(array):
    return '0x' in str(array.begin()) and '0x' in str(array.end())


def testRemoving(array):
    expect_array = arrayToList(array)
    expect_array.pop(3)
    array.pop(3)
    expect_array.pop(-1)
    array.pop_back()
    expect_array.pop(0)
    array.pop_front()
    if expect_array != arrayToList(array):
        return False
    return True


def testResize(array):
    expect_array = arrayToList(array)
    [expect_array.append(0) for i in range(3)]
    array.resize(array.size() + 3)
    if expect_array != arrayToList(array):
        return False

    expect_array = expect_array[:-5]
    array.resize(array.size() - 5)
    array.shrink_to_fit()
    if expect_array != arrayToList(array) or array.size() != array.capacity():
        return False
    return True


def testReverse(array):
    expect_array = arrayToList(array)
    expect_array[1], expect_array[2] = expect_array[2], expect_array[1]
    array.swap(1, 2)
    if expect_array != arrayToList(array):
        return False

    expect_array.reverse()
    array.reverse()
    if expect_array != arrayToList(array):
        return False
    return True


if __name__ == '__main__':
    arr1 = DynamicArrayProject.DynamicArray()
    arr2 = DynamicArrayProject.DynamicArray(4)
    arr = DynamicArrayProject.DynamicArray(4, ['1', 2, 3.14, '444'])

    tests = {}
    tests['Default constructor'] = testConstructor(arr1, [], 1)
    tests['Constructor with size'] = testConstructor(arr2, [0, 0, 0, 0], 8)
    tests['Constructor with size and elements'] = testConstructor(arr, ['1', 2, 3.14, '444'], 8)
    tests['Begin and End'] = testPointers(arr)
    tests['Push back, Push front, Insert'] = testAdding(arr)
    tests['Pop back, Pop front, Pop'] = testRemoving(arr)
    tests['Resize and Shrink-to-fit'] = testResize(arr)
    arr = DynamicArrayProject.DynamicArray(4, ['1', 2, 3.14, '444'])
    tests['Swap and Reverse'] = testReverse(arr)
    tests['Clear'] = testClear(arr)

    for name in tests:
        print('TESTING', '[' + name + ']', str(tests[name]).upper())
