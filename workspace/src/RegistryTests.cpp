#include "Kasa.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(
  KasaTests,
  RegistryPopulation_RandomizedProductCount_RegistrySizeMatchesGeneratedProductCount)
{
    Registry registry;
    std::random_device my_random_device;
    std::mt19937 my_generator(my_random_device());
    std::uniform_int_distribution<> distr(1, 100);
    int random_product_count = distr(my_generator);

    double price = 10.00;
    long identifier_aplifier = 10;
    for (int i = 0; i < random_product_count; ++i)
    {
        struct Product temp_product;
        temp_product.identifier = static_cast<long>(i * identifier_aplifier);
        temp_product.name = "Product";
        temp_product.price = price;
        registry.add(temp_product);
    }
    EXPECT_EQ(registry.getEntryCount(), random_product_count);
}

TEST(KasaTests,
     RegistryPopulation_IgnoreProductOfDuplicateId_ProductNotAddedToRegistry)
{
    Registry registry;
    long duplicate_identifier = 1;
    double random_price = 67.00;
    struct Product product_a(
      duplicate_identifier, "MyUniqueProduct", random_price);
    struct Product product_b(
      duplicate_identifier, "AnotherTotallyDifferentProduct", random_price);
    registry.add(product_a);
    registry.add(product_b);
    EXPECT_EQ(registry.getEntryCount(), 1);
}

TEST(
  KasaTests,
  RegistryDepopulation_RegistrySizeAfterDeletion_RegistrySizeIsDecrementedAfterDeletingOneProduct)
{
    Registry registry;
    std::random_device my_random_device;
    std::mt19937 my_generator(my_random_device());
    std::uniform_int_distribution<> distr(1, 100);
    int random_product_count = distr(my_generator);

    for (int i = 0; i < random_product_count; ++i)
    {
        struct Product temp_product;
        temp_product.identifier = i + 10;
        temp_product.name = "Product";
        temp_product.price = 10.00;
        registry.add(temp_product);
    }
    registry.del(registry.contents.begin()->second.identifier);
    EXPECT_EQ(registry.getEntryCount(), random_product_count - 1);
}
