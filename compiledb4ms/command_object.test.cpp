#include <gtest/gtest.h>

#include <compiledb4ms/command_object.h>

TEST(Command_object_tojson, each_item_will_be_quoted)
{
	Command_object obj{
		R"(C:\123)",
		R"(C:/456)",
		{ R"(C:\123)", R"(C:/456)" },
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
