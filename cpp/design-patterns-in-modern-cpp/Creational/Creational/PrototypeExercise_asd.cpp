struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
      return {new Point(*start), new Point(*end)};
  }
};

int main(){
    auto old_line = Line (new Point(0,0), new Point(1,1));
    auto new_line = old_line.deep_copy();
} 