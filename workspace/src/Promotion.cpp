#include "Promotion.hpp"

auto operator<<(std::ostream& output_stream,
                struct Promotion const& promotion) -> std::ostream&
{
    if (promotion.type == PromotionType::DISCOUNT)
    {
        output_stream << "[ " << (promotion.is_active ? "active" : "inactive")
                      << " | " << promotion.identifier << " -> "
                      << promotion.discount * 100 << "% OFF! ]";
    }
    else
    {
        output_stream << "[ " << (promotion.is_active ? "active" : "inactive")
                      << " | " << promotion.identifier << " -> "
                      << promotion.nth_free - 1 << " +1 GRATIS!! ]";
    }
    return output_stream;
}
