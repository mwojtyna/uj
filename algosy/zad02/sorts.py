def bubble_sort(nums: list[int]):
    for i in range(len(nums)):
        for j in range(len(nums) - i - 1):
            if nums[j] > nums[j + 1]:
                nums[j], nums[j + 1] = nums[j + 1], nums[j]


def insertion_sort(nums: list[int]):
    # i - index in unsorted part
    for i in range(1, len(nums)):
        # j - index in sorted part
        for j in range(0, i):
            if nums[i] < nums[j]:
                popped = nums.pop(i)
                nums.insert(j, popped)


def selection_sort(nums: list[int]):
    # i - index in unsorted part
    for i in range(len(nums)):
        # index of the smallest element in [i:]
        s = i

        # j - index in sorted part
        for j in range(i + 1, len(nums)):
            if nums[j] <= nums[s]:
                s = j

        nums[s], nums[i] = nums[i], nums[s]


def heap_sort(nums: list[int]):
    def heapify(n: int, i: int):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < n and nums[left] > nums[largest]:
            largest = left
        if right < n and nums[right] > nums[largest]:
            largest = right

        if largest != i:
            nums[i], nums[largest] = nums[largest], nums[i]
            heapify(n, largest)

    n = len(nums)
    for i in range(n // 2 - 1, -1, -1):
        heapify(n, i)

    for i in range(n - 1, 0, -1):
        nums[i], nums[0] = nums[0], nums[i]
        heapify(i, 0)


def quicksort(nums: list[int], lo: int = 0, hi: int | None = None):
    # For convenience
    if hi is None:
        hi = len(nums) - 1

    def partition(array: list[int], lo: int, hi: int) -> int:
        mid = lo + (hi - lo) // 2
        pivot = array[mid]
        array[mid], array[hi] = array[hi], array[mid]
        i = lo

        for j in range(lo, hi):
            if array[j] <= pivot:
                array[i], array[j] = array[j], array[i]
                i += 1

        array[i], array[hi] = array[hi], array[i]
        return i

    if lo < hi:
        pivot_index = partition(nums, lo, hi)
        quicksort(nums, lo, pivot_index - 1)
        quicksort(nums, pivot_index + 1, hi)


def merge_sort(nums: list[int], lo: int = 0, hi: int | None = None):
    # For convenience
    if hi is None:
        hi = len(nums) - 1

    def merge(nums: list[int], L: int, M: int, R: int):
        left = nums[L : M + 1]
        right = nums[M + 1 : R + 1]
        i = L
        l = 0
        r = 0

        while l < len(left) and r < len(right):
            if left[l] <= right[r]:
                nums[i] = left[l]
                l += 1
            else:
                nums[i] = right[r]
                r += 1
            i += 1

        while l < len(left):
            nums[i] = left[l]
            l += 1
            i += 1

        while r < len(right):
            nums[i] = right[r]
            r += 1
            i += 1

    if lo == hi:
        return

    mid = lo + (hi - lo) // 2
    merge_sort(nums, lo, mid)
    merge_sort(nums, mid + 1, hi)

    merge(nums, lo, mid, hi)
