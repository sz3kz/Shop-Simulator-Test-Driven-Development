#include "Product.hpp"
#include "World.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(
  KasaTests,
  ProductInitialization_ProductParameteredConstructorMembers_ProductConstructorParametersMatchObjectMembers)
{
    // Even though it technically breaks AAA, the functionality is connected
    // logically in such a way that it should be tested together nontheless.
    long expected_identifier = 10;
    std::string expected_name = "product";
    double expected_price = 10.00;
    struct Product product(expected_identifier, expected_name, expected_price);
    EXPECT_EQ(product.identifier, expected_identifier);
    EXPECT_EQ(product.name, expected_name);
    EXPECT_EQ(product.price, expected_price);
}

TEST(
  KasaTests,
  ProductInitialization_ProductInvalidId_ProductAssignedPredefinedInvalidIdentifierIfSuppliedIdentifierNotPositive)
{
    struct Product product(-20, "Product of a weird Id", 10);
    EXPECT_EQ(product.identifier, invalid_identifier);
}

TEST(
  KasaTests,
  ProductInitialization_ProductInvalidName_ProductAssignedPredefinedInvalidIdentifierIfSuppliedNameEmpty)
{
    struct Product product(10, "", 10.00);
    EXPECT_EQ(product.identifier, invalid_identifier);
}

TEST(
  KasaTests,
  ProductInitialization_ProductInvalidPrice_ProductAssignedPredefinedInvalidIdentifierIfSuppliedPriceNegative)
{
    struct Product product(10, "The Best deal you have ever seen!", -10.00);
    EXPECT_EQ(product.identifier, invalid_identifier);
}
