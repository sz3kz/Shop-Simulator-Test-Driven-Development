#include "Kasa.hpp"
#include <algorithm>

void addProduct(Registry& registry, struct Product const& product)
{
    if (std::any_of(registry.begin(),
                    registry.end(),
                    [product](auto temp_product)
                    { return temp_product.id == product.id; }))
        return;
    registry.push_back(product);
}
