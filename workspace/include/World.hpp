#pragma once
#include <cstdint>

constexpr int loyalty_card_identifier = 9999;
constexpr long invalid_identifier = -1;

enum class PromotionType : std::uint8_t
{
    DISCOUNT, // price is lowever by price * DISCOUNT
    BULK      // for every n products, 1 is free
};
