val nums = (1 to 10).toList

nums.filter(_ < 4)
nums.span(_ % 4 != 0)
nums.partition(_ % 4 != 0)

// will not compile, as the param can't be used twice
// nums.map(_ * _)
// have to use
nums.map(x => x * x)
// instead

def compareNeighbors(xs: List[Int], compare: (Int, Int) => Int): List[Int] = {
  for (pair <- xs.sliding(2)) yield {
    compare(pair(0), pair(1))
  }
}.toList

compareNeighbors(nums, _ + _)

// will not compile, _s in ()s mean something else
// compareNeighbors(List(4, 1, 7, 3, 4, 8), (_ - _).abs)

compareNeighbors(nums, _ + _)  // can infer types
compareNeighbors(nums, (_: Int) + (_: Int))  // explicit types

val addPair = (_: Int) + (_: Int)
compareNeighbors(nums, addPair)

val addPair2 = (a: Int, b: Int) => a + b
compareNeighbors(nums, addPair2)
