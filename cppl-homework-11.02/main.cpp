//
//  main.cpp
//  cppl-homework-11.02
//
//  Created by a1ex on 3/12/24.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <class T>
class big_integer
{
private:
    std::vector<T> v1;
public:
    big_integer()
{
    v1.push_back(0);
}
    big_integer(const std::string& str)
{
    for (int i = str.size() - 1; i >= 0; i--)
      {
        v1.push_back(str[i] - '0');
      }
}
big_integer(const std::vector<T>& v) : v1(v) {}
big_integer(const big_integer& other) noexcept
{
    v1 = other.v1;
}
big_integer(big_integer&& other) noexcept
{
    v1 = std::move(other.v1);
}
big_integer& operator=(const big_integer& other)
{
    v1 = other.v1;
    return *this;
}
big_integer& operator=(big_integer&& other)
{
    v1 = std::move(other.v1);
    return *this;
}
big_integer operator+(const big_integer& other)
{
    big_integer<T> result;
    big_integer<T> new_other = other;
    big_integer<T> new_other2 = v1;
  if (new_other.v1.size() > new_other2.v1.size())
  {
    while(new_other2.v1.size() != new_other.v1.size())
      {
    new_other2.v1.insert(new_other2.v1.begin(), 0);
      }
  }
  else if (new_other.v1.size() < new_other2.v1.size())
  {
    while (new_other.v1.size() != new_other2.v1.size())
      {
    new_other.v1.insert(new_other.v1.begin(), 0);
      }
  }
    for(int i = 0; i < v1.size(); i++)
      {
        result.v1.push_back(v1[i] + other.v1[i]);
        if(result.v1[i] > 9)
        {
          result.v1[i] -= 10;
          result.v1[i + 1] += 1;
        }
      }
    while (result.v1.size() > 1 && result.v1.back() == 0)
    {
      result.v1.pop_back();
    }
    return result;
}
const big_integer operator*(const big_integer& other)
{
  big_integer result;
  result.v1.resize(v1.size() + other.v1.size());
  for (size_t i = 0; i < v1.size(); ++i)
  {
    int carry = 0;
    for (size_t j = 0; j < other.v1.size() || carry != 0; ++j)
    {
      long long cur = result.v1[i + j] + v1[i] * 1LL * (j < other.v1.size() ? other.v1[j] : 0) + carry;
      result.v1[i + j] = static_cast<int>(cur % 10);
      carry = static_cast<int>(cur / 10);
    }
  }
  while (result.v1.size() > 1 && result.v1.back() == 0)
    {
      result.v1.pop_back();
    }
  return result;
}
friend std::ostream& operator<<(std::ostream& os, const big_integer<T>& bigint)
{
    for (auto it = bigint.v1.rbegin(); it != bigint.v1.rend(); ++it)
    {
        os << *it;
    }
    return os;
}

};

int main(int argc, const char * argv[]) {


  auto number1 = big_integer<int>("114575");
  auto number2 = big_integer<int>("78524");
  auto result = number1 + number2;
    std::cout << result << '\n'; // 193099

   auto result2 = number1 * number2;
     std::cout << result2 << '\n';


    return 0;
}
