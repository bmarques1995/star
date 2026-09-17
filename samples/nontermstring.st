/*auto x = 485u32;
print(x);
{
    auto y = 85u32;
    y = x;
    print(y);
}
*/

auto a = "global";
{
  fun showA() {
    print(a);
  }

  showA();
  auto a = "block";
  showA();
}
