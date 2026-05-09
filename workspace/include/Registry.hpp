#pragma once
#include "Product.hpp"
#include "Promotion.hpp"
#include <map>

struct Registry
{
    std::map<long, Product> contents;
    std::map<long, Promotion> promotions;
    bool loyalty_card_active{ false };
    void add(struct Product const& product);
    void activateLoyaltyCard();
    void deactivateLoyaltyCard();
    void addPromotion(long identifier, double discount);
    void addPromotion(long identifier, int nth_free);
    void activatePromotion(long identifier);
    void deactivatePromotion(long identifier);
    void updatePromotionStatus();
    void del(long identifier);
    [[nodiscard]] auto getEntryCount() const -> size_t;
    void print() const;
};
