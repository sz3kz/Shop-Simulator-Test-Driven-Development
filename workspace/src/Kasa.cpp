#include "Kasa.hpp"
#include <algorithm>

void registerProduct(Registry& registry, struct Product const& product)
{
    registry.emplace(product.identifier, product);
}

void deregisterProduct(Registry& registry, long identifier)
{
    registry.erase(identifier);
}

void cartAddProduct(Registry const& registry, Cart& cart, long identifier)
{
    if (registry.contains(identifier))
    {
        cart.push_back(identifier);
    }
}

void cartDeleteProduct(Cart& cart, long identifier)
{
    auto iterator = std::find_if(cart.begin(),
                                 cart.end(),
                                 [identifier](auto current_identifier)
                                 { return current_identifier == identifier; });
    if (iterator == cart.end())
    {
        return;
    }
    cart.erase(iterator);
}
