#include "Registry.hpp"
#include "World.hpp"

void Registry::add(struct Product const& product)
{
    if (product.identifier != invalid_identifier)
    {
        contents.emplace(product.identifier, product);
    }
}

void Registry::activateLoyaltyCard()
{
    loyalty_card_active = true;
}

void Registry::deactivateLoyaltyCard()
{
    loyalty_card_active = false;
}

void Registry::updatePromotionStatus()
{
    for (auto const& pair : promotions)
    {
        if (loyalty_card_active)
        {
            activatePromotion(pair.first);
        }
        else
        {
            deactivatePromotion(pair.first);
        }
    }
}

void Registry::addPromotion(long identifier, double discount)
{
    // Registers a DISCOUNT-type promotion.
    // Only if identifier is of a registered product.
    auto iterator = contents.find(identifier);
    if (iterator == contents.end())
    {
        return;
    }
    promotions.emplace(identifier,
                       Promotion(PromotionIdentifier(identifier), discount));
}

/**
 * @brief Registers a new bulk-type promotion for a specific product.
 * * This function creates and stores a `Promotion` object of type `BULK`
 * associated with the provided product identifier. The promotion is only
 * added if the product ID already exists within the registry's contents.
 * #AIGenerated
 * * @param identifier The unique long identifier of the product to receive the
 * promotion.
 * @param nth_free An integer specifying the "buy N, get one free" threshold
 * (e.g., if nth_free is 3, every 3rd item is free).
 * * @note If the @p identifier is not found in the @c contents map, the
 * function returns silently without adding a promotion.
 * * @see Promotion, PromotionType
 */
void Registry::addPromotion(long identifier, int nth_free)
{
    auto iterator = contents.find(identifier);
    if (iterator == contents.end())
    {
        return;
    }

    promotions.emplace(identifier,
                       Promotion(PromotionIdentifier(identifier), nth_free));
}

void Registry::activatePromotion(long identifier)
{
    auto iterator = promotions.find(identifier);
    if (iterator == promotions.end())
    {
        return;
    }
    Promotion promotion = iterator->second;
    promotion.is_active = true;
    promotions.insert_or_assign(identifier, promotion);
}

void Registry::deactivatePromotion(long identifier)
{
    auto iterator = promotions.find(identifier);
    if (iterator == promotions.end())
    {
        return;
    }
    Promotion promotion = iterator->second;
    promotion.is_active = false;
    promotions.insert_or_assign(identifier, promotion);
}

void Registry::del(long identifier)
{
    contents.erase(identifier);
}

[[nodiscard]]
auto Registry::getEntryCount() const -> size_t
{
    return contents.size();
}

void Registry::print() const
{
    for (auto const& pair : contents)
    {
        std::cout << pair.second << '\n';
    }
}
