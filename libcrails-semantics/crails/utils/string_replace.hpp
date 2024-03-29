#ifndef  CRAILS_STRING_REPLACE_HPP
# define CRAILS_STRING_REPLACE_HPP

# include <string>
# include <string_view>
# include <functional>
# include <regex>

namespace Crails
{
  std::string replace_all_occurences(std::string data, const std::string_view pattern, const std::string_view filler);
  std::string replace_all_occurences(const std::string& data, const std::regex& pattern, const std::string_view filler);
  std::string replace_all_occurences(const std::string& data, const std::regex& pattern, std::function<std::string(const std::string_view)> filler);
}

#endif
