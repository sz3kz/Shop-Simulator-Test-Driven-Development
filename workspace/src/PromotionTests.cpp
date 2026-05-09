#include "Cart.hpp"
#include "Product.hpp"
#include "Registry.hpp"
#include "World.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(KasaTests,
     Promotions_ActivatingLoyaltyCard_RegistryActivatesLoyaltyCardViaMethod)
{
    Registry registry;
    registry.activateLoyaltyCard();
    EXPECT_EQ(registry.loyalty_card_active, true);
}

TEST(KasaTests,
     Promotions_DeactivatingLoyaltyCard_RegistryDeactivatesLoyaltyCardViaMethod)
{
    Registry registry;
    registry.activateLoyaltyCard();
    registry.deactivateLoyaltyCard();
    EXPECT_EQ(registry.loyalty_card_active, false);
}

TEST(
  KasaTests,
  Promotions_PromotionRegistration_RegistryCorrectlyRegistersDiscountPromotion)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 0.2);
    EXPECT_EQ(registry.promotions.at(10).type, PromotionType::DISCOUNT);
    EXPECT_EQ(registry.promotions.at(10).discount, 0.2);
    EXPECT_EQ(registry.promotions.at(10).nth_free, 0);
    EXPECT_EQ(registry.promotions.at(10).is_active, false);
}

TEST(
  KasaTests,
  Promotions_PromotionRegistration_RegistryDoesNotRegisterDiscountPromotionForInvalidProduct)
{
    Registry registry;
    registry.addPromotion(10, 0.2);
    EXPECT_EQ(registry.promotions.size(), 0);
}

TEST(KasaTests,
     Promotions_PromotionRegistration_RegistryCorrectlyRegistersBulkPromotion)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 5);
    EXPECT_EQ(registry.promotions.at(10).type, PromotionType::BULK);
    EXPECT_EQ(registry.promotions.at(10).discount, 0.0);
    EXPECT_EQ(registry.promotions.at(10).nth_free, 5);
    EXPECT_EQ(registry.promotions.at(10).is_active, false);
}

TEST(
  KasaTests,
  Promotions_PromotionRegistration_RegistryDoesNotRegisterBulkPromotionForInvalidProduct)
{
    Registry registry;
    registry.addPromotion(10, 3);
    EXPECT_EQ(registry.promotions.size(), 0);
}

TEST(
  KasaTests,
  Promotions_PromotionRegistrationForSameProductIdentifier_RegistryIgnoresPromotionRegistrationForIdentifierWithAlreadyRegisteredPromotion)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 0.2);
    registry.addPromotion(10, 5);
    EXPECT_EQ(registry.promotions.at(10).type, PromotionType::DISCOUNT);
}

TEST(KasaTests,
     Promotions_PromotionActivation_RegistryCorrectlyActivatesPromotion)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 5);
    registry.activatePromotion(10);
    EXPECT_EQ(registry.promotions.at(10).is_active, true);
}

TEST(KasaTests,
     Promotions_PromotionActivation_RegistryCorrectlyDeactivatesPromotion)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 5);
    registry.activatePromotion(10);
    registry.deactivatePromotion(10);
    EXPECT_EQ(registry.promotions.at(10).is_active, false);
}

TEST(
  KasaTests,
  Promotions_PromotionStatusUpdateViaLoyaltyCard_RegistryCorrectlyActivatesPromotionsBasedOnActivatedLoyaltyCard)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.add(Product(9, "banana", 10.00));
    registry.addPromotion(10, 5);
    registry.addPromotion(9, 0.2);
    registry.activateLoyaltyCard();
    registry.updatePromotionStatus();
    EXPECT_EQ(registry.promotions.at(10).is_active, true);
    EXPECT_EQ(registry.promotions.at(9).is_active, true);
}

TEST(
  KasaTests,
  Promotions_PromotionStatusUpdateViaLoyaltyCard_RegistryCorrectlyActivatesPromotionsBasedOnDeactivatedLoyaltyCard)
{
    Registry registry;
    registry.add(Product(10, "apple", 10.00));
    registry.add(Product(9, "banana", 10.00));
    registry.addPromotion(10, 5);
    registry.addPromotion(9, 0.2);

    registry.activateLoyaltyCard();
    registry.updatePromotionStatus();

    registry.deactivateLoyaltyCard();
    registry.updatePromotionStatus();

    EXPECT_EQ(registry.promotions.at(10).is_active, false);
    EXPECT_EQ(registry.promotions.at(9).is_active, false);
}

TEST(
  KasaTests,
  CartCardAddition_RegisteringCardViaProductAdd_LoyaltyCardActivatesWhenRegisteringCorrectIdentifier)
{
    Registry registry;
    Cart cart;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 5);
    cart.add(registry, loyalty_card_identifier);
    EXPECT_EQ(registry.promotions.at(10).is_active, true);
}

TEST(
  KasaTests,
  CartCardAddition_UnregisteringCardViaProductAdd_LoyaltyCardDeactivatesWhenRegisteringCorrectIdentifier)
{
    Registry registry;
    Cart cart;
    registry.add(Product(10, "apple", 10.00));
    registry.addPromotion(10, 5);
    cart.add(registry, loyalty_card_identifier);
    cart.add(registry, loyalty_card_identifier);
    EXPECT_EQ(registry.promotions.at(10).is_active, false);
}

TEST(KasaTests,
     CartClosing_LoyaltyCardDeactivation_CardIsDeactivatedWhenClosingCart)
{
    Registry registry;
    Cart cart;
    cart.add(registry, loyalty_card_identifier);
    cart.close(registry);
    EXPECT_EQ(registry.loyalty_card_active, false);
}
