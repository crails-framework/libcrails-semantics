#ifndef  CRAILS_SEMANTICS_JOIN_HPP
# define CRAILS_SEMANTICS_JOIN_HPP

# include <sstream>

namespace Crails
{
  template<typename ITERATOR, typename SEPARATOR = char>
  std::string join(ITERATOR begin, ITERATOR end, SEPARATOR separator = ' ')
  {
    std::stringstream stream;

    for (ITERATOR it = begin; it != end ; ++it)
    {
      if (separator && it != begin) stream << separator;
      stream << *it;
    }
    return stream.str();
  }

  template<typename LIST, typename SEPARATOR = char>
  std::string join(const LIST& list, SEPARATOR separator = ' ')
  {
    return join(list.begin(), list.end(), separator);
  }
}

#endif
