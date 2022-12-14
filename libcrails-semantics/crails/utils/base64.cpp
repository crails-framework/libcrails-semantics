#include "base64.hpp"

using namespace std;

static const string  charset_64 =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789+/";

static inline bool is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

namespace Crails
{
  string base64_encode(const string& str_to_encode)
  {
    return (base64_encode((unsigned char const*)str_to_encode.c_str(), str_to_encode.size()));
  }

  string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
  {
    string        ret;
    int           i = 0;
    int           j = 0;
    unsigned char array_3[3];
    unsigned char array_4[4];

    while (in_len--) {
      array_3[i++] = *(bytes_to_encode++);
      if (i == 3) {
        array_4[0] = (array_3[0] & 0xfc) >> 2;
        array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4);
        array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
        array_4[3] = array_3[2] & 0x3f;

        for(i = 0; (i <4) ; i++)
          ret += charset_64[array_4[i]];
        i = 0;
      }
    }

    if (i)
    {
      for(j = i; j < 3; j++)
        array_3[j] = '\0';
      array_4[0] = (array_3[0] & 0xfc) >> 2;
      array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4);
      array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
      array_4[3] = array_3[2] & 0x3f;
      for (j = 0; (j < i + 1); j++)
        ret += charset_64[array_4[j]];
      while((i++ < 3))
        ret += '=';
    }
    return (ret);
  }

  string base64_decode(const string& encoded_string)
  {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
      char_array_4[i++] = encoded_string[in_]; in_++;
      if (i == 4)
      {
        for (i = 0; i <4; i++)
          char_array_4[i] = charset_64.find(char_array_4[i]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (i = 0; (i < 3); i++)
          ret += char_array_3[i];
        i = 0;
      }
    }
    if (i)
    {
      for (j = i; j < 4; j++)
        char_array_4[j] = 0;
      for (j = 0; j < 4; j++)
        char_array_4[j] = charset_64.find(char_array_4[j]);
      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
      for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
  }
}
