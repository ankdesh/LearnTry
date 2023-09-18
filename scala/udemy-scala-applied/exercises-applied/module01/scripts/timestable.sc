var x = 10
var y = 20
while (x >=0 ){
  while (y >=0 ){
    var m = x * y
    if (m.toString.contains("4") || m.toString.contains("6")) println(s"$x times $y is $m") 
    y -= 1
  }
  x -= 1
}

