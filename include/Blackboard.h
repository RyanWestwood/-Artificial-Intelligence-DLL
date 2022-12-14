#pragma once
#include <map>
#include <memory>
#include <string>

namespace ai
{
  typedef std::shared_ptr<bool>  BoolPtr;
  typedef std::shared_ptr<float> FloatPtr;
  typedef std::shared_ptr<int>   IntPtr;
  typedef std::string            Key;

  class Blackboard
  {
  public:
    Blackboard();
    Blackboard(std::string filename);

    FloatPtr GetFloat(Key name, float default_value);
    BoolPtr  GetBool(Key name, bool default_value);
    IntPtr   GetInt(Key name, int default_value);

  private:
    void ReadFile();
    void WriteFile();
    void PrintBoard();

  private:
    std::map<Key, FloatPtr> m_Floats;
    std::map<Key, BoolPtr>  m_Bools;
    std::map<Key, IntPtr>   m_Ints;
    std::string             m_Filename;
  };
} // namespace ai