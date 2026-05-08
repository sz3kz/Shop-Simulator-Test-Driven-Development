#pragma once
#include "Product.hpp"
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

constexpr int loyalty_card_identifier = 9999;

enum class PromotionType
{
    DISCOUNT, // price is lowever by price * DISCOUNT
    BULK      // for every n products, 1 is free
};

struct Promotion
{
    long identity{ 0 };
    PromotionType type;
    double discount{ 0.0 };
    int nth_free{ 0 };
    bool is_active{ false };
    friend auto operator<<(std::ostream& output_stream,
                           struct Promotion const& promotion) -> std::ostream&;
};

struct Registry
{
    std::map<long, Product> contents;
    std::map<long, Promotion> promotions;
    bool loyalty_card_active{ false };
    void add(struct Product const& product);
    void activate_loyalty_card();
    void deactivate_loyalty_card();
    void add_promotion(long identity, double discount);
    void add_promotion(long identity, int nth_free);
    void activate_promotion(long identity);
    void deactivate_promotion(long identity);
    void update_promotion_status();
    void del(long identifier);
    [[nodiscard]] auto getEntryCount() const -> size_t;
    void print() const;
    void print_promotions() const;
};

struct Cart
{
    std::vector<long> contents;
    void add(Registry& registry, long identifier);
    void del(long identifier);
    [[nodiscard]] auto calculateValue(Registry const& registry) const -> double;
    [[nodiscard]] auto getEntryCount() const -> size_t;
    void close(Registry& registry);
    void print(Registry const& registry) const;
};
