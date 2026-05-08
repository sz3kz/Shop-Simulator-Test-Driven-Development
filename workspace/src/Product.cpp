#include "Product.hpp"

auto operator<<(std::ostream& output_stream,
                struct Product const& product) -> std::ostream&
{
    output_stream << "(" << product.identifier << "|\"" << product.name << "\"|"
                  << product.price << ")";
    return output_stream;
}
