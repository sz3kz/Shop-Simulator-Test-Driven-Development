#pragma once
#include "World.hpp"

struct PromotionIdentifier
{
    long value;
    explicit PromotionIdentifier(long identifier)
      : value(identifier)
    {
    }
};

struct Promotion
{
    long identifier{ 0 };
    PromotionType type{ 0 };
    double discount{ 0.0 };
    int nth_free{ 0 };
    bool is_active{ false };
    Promotion(PromotionIdentifier identifier_wrapper, double discount_value)
      : identifier(identifier_wrapper.value)
      , type(PromotionType::DISCOUNT)
      , discount(discount_value)
    {
    }
    Promotion(PromotionIdentifier identifier_wrapper, int discount_value)
      : identifier(identifier_wrapper.value)
      , type(PromotionType::BULK)
      , nth_free(discount_value)
    {
    }
};
