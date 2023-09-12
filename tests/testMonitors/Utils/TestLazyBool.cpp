#include "Utils/LazyBool.h"
#include "TestLazyBool.h"

TEST(TestLazyBool, testFixedValue){
    LazyBool t(true);
    EXPECT_TRUE(static_cast<bool>(t));
    LazyBool f(false);
    EXPECT_FALSE(static_cast<bool>(f));
    LazyBool d;
    EXPECT_FALSE(static_cast<bool>(d));
}

TEST(TestLazyBool, testLazyEvaluation){
    std::function<bool()> t = [](){return true;};
    std::function<bool()> f = [](){return false;};
    LazyBool lazyBoolTrue(t);
    EXPECT_TRUE(static_cast<bool>(lazyBoolTrue));
    LazyBool lazyBoolFalse(f);
    EXPECT_FALSE(static_cast<bool>(lazyBoolFalse));
}