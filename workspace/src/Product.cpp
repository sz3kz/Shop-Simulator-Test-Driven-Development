#include "Product.hpp"
#include "World.hpp"

long Product::determine_id(long supplied_id,
                           std::string const& product_name,
                           double product_price)
{
    bool id_negative = (supplied_id <= 0);
    bool id_loyalty_card_reserved(supplied_id == loyalty_card_identifier);
    bool product_name_empty = (product_name.empty());
    bool product_price_negative = (product_price < 0);
    if (id_negative || id_loyalty_card_reserved || product_name_empty ||
        product_price_negative)
    {
        return invalid_identifier;
    }
    return supplied_id;
}

auto operator<<(std::ostream& output_stream,
                struct Product const& product) -> std::ostream&
{
    output_stream << "(" << product.identifier << "|\"" << product.name << "\"|"
                  << product.price << ")";
    return output_stream;
}
