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
          determine_id(product_identifier, product_name, product_price))
      , name(std::move(product_name))
      , price(product_price) {};
    static long determine_id(long supplied_id,
                             std::string const& product_name,
                             double product_price);
    friend auto operator<<(std::ostream& output_stream,
                           struct Product const& product) -> std::ostream&;
};
