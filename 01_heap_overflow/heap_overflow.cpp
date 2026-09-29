#include <string>
#include <gtest/gtest.h>

std::string make_label(const std::string& name) {  
    char* buf = new char[name.size()]; // no +1
    for (std::size_t i = 0; i <= name.size(); ++i)
        buf[i] = name[i];        // copies '\0' too
  
    std::string label(buf);
    delete[] buf;
    
    return label;
}

TEST(Label, CopiesName) {
  EXPECT_EQ(make_label("sensor"), "sensor");
}