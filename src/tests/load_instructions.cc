#include <gtest/gtest.h>
#include <string>
#include "VM.hh"

namespace star
{
    TEST(vm, sample)
    {
        std::vector<size_t> instructions =
        {
            0x4001000300000248, // PUSH_LOW instruction with value 137, register index 137 (STATUS)
            0x4002000300000001, // PUSH_LOW instruction with value 137, register index 137 (STATUS)
			0x4000008900000000, // EXIT instruction with exit code 0, register index 137 (STATUS)
        };
        VM vm{ instructions };
        EXPECT_NO_THROW(vm.Run());
    }
}
