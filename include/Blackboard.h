#pragma once
#include <map>
#include <string>
#include <memory>

namespace ai {

	class Blackboard;
	typedef std::shared_ptr<Blackboard> BlackboardPtr;
	typedef std::shared_ptr<bool> BoolPtr;
	typedef std::shared_ptr<float> FloatPtr;
	typedef std::shared_ptr<int> IntPtr;

	class Blackboard{
	public:
		Blackboard() {}
		void Initialize(std::string filename);

		FloatPtr GetFloat(std::string name, float default_value);
		BoolPtr GetBool(std::string name, bool default_value);
		IntPtr GetInt(std::string name, int default_value);

	private:
		void ReadFile();
		void WriteFile();
		void PrintBoard();

	private:
		std::map<std::string, FloatPtr> m_Floats;
		std::map<std::string, BoolPtr> m_Bools;
		std::map<std::string, IntPtr> m_Ints;
		std::string m_Filename;
	};
	
	BlackboardPtr CreateBlackboard(std::string filename);
} // namespace ai