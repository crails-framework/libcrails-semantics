#ifndef  CRAILS_SEMANTICS_JOIN_HPP
# define CRAILS_SEMANTICS_JOIN_HPP

# include <sstream>

namespace Crails
{
  template<typename ITERATOR>
  std::string join(ITERATOR begin, ITERATOR end, char separator = 0)
  {
    std::stringstream stream;

    for (ITERATOR it = begin; it != end ; ++it)
    {
      if (separator && it != begin) stream << separator;
      stream << *it;
    }
    return stream.str();
  }

  template<typename LIST>
  std::string join(const LIST& list, char separator = 0)
  {
    return join(list.begin(), list.end(), separator);
  }
}

#endif
