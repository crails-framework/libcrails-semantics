#ifndef  CRAILS_SEMANTICS_SPLIT_HPP
# define CRAILS_SEMANTICS_SPLIT_HPP

# include <list>

namespace Crails
{
  template<typename VALUE_TYPE, typename LIST_TYPE = std::list<VALUE_TYPE>>
  LIST_TYPE split(const VALUE_TYPE& str, char c, bool count_repetitions = false)
  {
    LIST_TYPE ret;
    long      last_sep = -1;
    size_t    i;

    for (i = 0 ; i < str.size() ; ++i)
    {
      if (str[i] == c)
      {
        size_t segment_length = i - static_cast<size_t>(last_sep + 1);

        if (count_repetitions || segment_length > 0)
          ret.push_back(str.substr(static_cast<size_t>(last_sep + 1), segment_length));
        last_sep = static_cast<long>(i);
      }
    }
    {
      size_t segment_length = str.size() - static_cast<size_t>(last_sep + 1);

      if (count_repetitions || segment_length > 0)
        ret.push_back(str.substr(static_cast<size_t>(last_sep + 1)));
    }
    return (ret);
  }
}

#endif
