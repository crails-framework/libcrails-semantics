#ifndef  CRAILS_SEMANTICS_HPP
# define CRAILS_SEMANTICS_HPP

# include <string>
# include <list>

namespace Crails
{
  enum CamelizeOption {
    UpperCamelcase,
    LowerCamelcase
  };

  bool        is_alphanumerical(char);
  std::string remove_duplicate_characters(const std::string&, char character);
  std::string underscore(const std::string&);
  std::string camelize(const std::string&, CamelizeOption = UpperCamelcase);
  std::string dasherize(const std::string&);
  std::string humanize(const std::string&);
  std::string strip(const std::string&, char character = ' ');
  std::string singularize(const std::string&);
  std::string pluralize(const std::string&);
}

#endif
