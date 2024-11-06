#include <iostream>

static void  encode(std::string str, const std::string &strbase, const int offset);

static void  decode(std::string str, const std::string &strbase, const int offset);

static int  getopt(const std::string &arg);

int  main(int argc, char **argv)
{
  std::string  strbase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
  std::string  str = "";
  int          offset = 42;
  bool         isEncode = false;
  bool         isDecode = false;

  int i = 1;
  while (i < argc)
  {
    switch (getopt(argv[i]))
      {
        case (1):
          strbase = argv[++i];
          break ;
        case (2):
          isDecode = true;
          break ;
        case (3):
          isEncode = true;
          break ;
        case (4):
          offset = atoi(argv[++i]);
          break ;
        default:
          str = argv[i];
          break ;
      }
    i ++;
  }
  if (isEncode == isDecode || str.empty())
    return (2);
  offset %= strbase.size();
  if (isEncode)
    encode(str, strbase, offset);
  else
    decode(str, strbase, offset);
  return (0);
}

static void  encode(std::string str, const std::string &strbase, const int offset)
{
  std::string::iterator it = str.begin();
  size_t                idx;

  while (it != str.end())
  {
    idx = strbase.find(*it);
    if (idx != std::string::npos)
      *it = strbase[(idx + offset) % strbase.size()];
    it++;
  }
  std::cout << str << std::endl;
}

static void  decode(std::string str, const std::string &strbase, const int offset)
{
  std::string::iterator it = str.begin();
  size_t                idx;
  int                   newOff = 0;

  while (it != str.end())
  {
    idx = strbase.find(*it);
    if (idx != std::string::npos)
    {
      *it = strbase[(idx - offset + strbase.size()) % strbase.size()];
    }
    it ++;
  }
  std::cout << str << std::endl;
}

static int  getopt(const std::string &arg)
{
  std::string    opts[] = {"-b", "-d", "-e", "-o"};

  for (int i = 0; i < 4; ++i)
    if (arg == opts[i])
      return (i + 1);
  return (0);
}
