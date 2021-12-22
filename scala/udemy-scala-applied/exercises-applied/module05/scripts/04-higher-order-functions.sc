val nums = (1 to 10).toList

nums.map(x => x * x)
nums.filter(x => x < 4)
nums.span(x => x % 4 != 0)
nums.partition(x => x % 4 != 0)


def compareNeighbors(xs: List[Int], compare: (Int, Int) => Int): List[Int] = {
  for (pair <- xs.sliding(2)) yield {
    compare(pair(0), pair(1))
  }
}.toList

compareNeighbors(nums, (a, b) => a + b)

compareNeighbors(List(4, 1, 7, 3, 4, 8), (a, b) => (a - b).abs)
