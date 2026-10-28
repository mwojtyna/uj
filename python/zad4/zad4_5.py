# Zadanie 4.5: odwracanie iteracyjnie i rekurencyjnie


def odwracanie_iter(nums, left: int, right: int):
    if not 0 <= left < len(nums):
        raise ValueError("left out of bounds")
    if not 0 <= right < len(nums):
        raise ValueError("right out of bounds")

    while left < right:
        nums[left], nums[right] = nums[right], nums[left]
        left += 1
        right -= 1


def odwracanie_rec(nums, left: int, right: int):
    if not 0 <= left < len(nums):
        raise ValueError("left out of bounds")
    if not 0 <= right < len(nums):
        raise ValueError("right out of bounds")

    if left >= right:
        return

    nums[left], nums[right] = nums[right], nums[left]
    odwracanie_rec(nums, left + 1, right - 1)


if __name__ == "__main__":
    print("Iteracyjnie:")
    nums = [1, 2, 3, 4, 5]
    print("Przed odwróceniem:", nums)
    odwracanie_iter(nums, 0, 3)
    assert nums == [4, 3, 2, 1, 5]
    print(f"Po odwróceniu (left={0}, right={3}):", nums)

    print("\nRekurencyjnie:")
    nums = [1, 2, 3, 4, 5]
    print("Przed odwróceniem:", nums)
    odwracanie_rec(nums, 1, 4)
    assert nums == [1, 5, 4, 3, 2]
    print(f"Po odwróceniu (left={1}, right={4}):", nums)
