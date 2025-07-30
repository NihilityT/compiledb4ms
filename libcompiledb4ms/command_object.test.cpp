#include <gtest/gtest.h>

#include <libcompiledb4ms/command_object.h>

using namespace compiledb4ms;

TEST(Command_object_tojson, each_item_will_be_quoted)
{
	Command_object obj{
		R"(C:\123)",
		R"(C:/456)",
		std::vector<std::string>{
			R"(C:\123)",
			R"(C:/456)",
		},
	};

	ASSERT_EQ(obj.str(), R"({
  "directory": "C:\\123",
  "file": "C:/456",
  "arguments": [
    "C:\\123",
    "C:/456"
  ]
})");
}

TEST(Command_object_tojson, use_command_when_arguments_is_not_exists)
{
	Command_object obj;
	obj.arguments = R"("C:\123.exe" a b "c/d" "a s")";

	constexpr auto expected = R"({
  "directory": "",
  "file": "",
  "command": "\"C:\\123.exe\" a b \"c/d\" \"a s\""
})";
	ASSERT_EQ(obj.str(), expected);
}
