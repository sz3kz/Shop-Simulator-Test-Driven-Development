#pragma once
#include <string>
#include <vector>

struct Product
{
    long id{ 0 };
    std::string name{ "" };
    double price{ 0 };

    Product() = default;
};

using Registry = std::vector<Product>;

void addProduct(Registry& registry, struct Product const& product);
