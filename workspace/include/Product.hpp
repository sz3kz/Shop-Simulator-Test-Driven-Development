#pragma once
#include <iostream>
#include <string>

struct Product
{
    long identifier;
    std::string name;
    double price;

    explicit Product(long product_identifier,
                     std::string product_name,
                     double product_price)
      : identifier(
          determineIdentifier(product_identifier, product_name, product_price))
      , name(std::move(product_name))
      , price(product_price) {};
    static auto determineIdentifier(long supplied_id,
                                    std::string const& product_name,
                                    double product_price) -> long;
    friend auto operator<<(std::ostream& output_stream,
                           struct Product const& product) -> std::ostream&;
};
