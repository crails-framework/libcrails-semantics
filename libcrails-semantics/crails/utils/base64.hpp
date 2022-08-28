#ifndef  CRAILS_SEMANTICS_BASE64_HPP
# define CRAILS_SEMANTICS_BASE64_HPP

# include <string>

namespace Crails
{
  std::string base64_encode(unsigned char const* str, unsigned int len);
  std::string base64_encode(const std::string& str_to_encode);
  std::string base64_decode(const std::string& str_to_decode);
}

#endif
