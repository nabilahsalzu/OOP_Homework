#include <iostream>
#include <vector>
#include <string>

struct Product {
  int id;
  std::string name;
  double price;
};

class Catalog {
public:
  std::vector<Product> catalog;

  void load_catalog() {
    catalog.push_back({1, "Apple", 0.5});
    catalog.push_back({2, "Bread", 1.5});
    catalog.push_back({3, "Milk", 2.0});
    catalog.push_back({4, "Chocolate", 1.0});
  }

  Product* find_product(int id) {
    for (auto &p : catalog) if (p.id == id) return &p;
    return nullptr;
  }
};

class Cart {
public:
  std::vector<int> cart_ids;
  std::vector<int> cart_qty;

  void add_to_cart(int id, int qty) {
    for (size_t i=0;i<cart_ids.size();++i) {
      if (cart_ids[i] == id) { cart_qty[i] += qty; return; }
    }
    cart_ids.push_back(id);
    cart_qty.push_back(qty);
  }

  void remove_from_cart(int id) {
    for (size_t i = 0; i < cart_ids.size(); ++i) {
      if (cart_ids[i] == id) {
        cart_ids.erase(cart_ids.begin() + i);
        cart_qty.erase(cart_qty.begin() + i);
        return;
      }
    }
  }
};

class Checkout {
public:
  double TAX_RATE = 0.07;

  double compute_subtotal(Cart& cart, Catalog& catalog) {
    double s = 0.0;
    for (size_t i=0;i<cart.cart_ids.size();++i) {
      Product* p = catalog.find_product(cart.cart_ids[i]);
      if (p) s += p->price * cart.cart_qty[i];
    }
    return s;
  }

  double apply_discounts(double subtotal) {
    if (subtotal > 10.0) return subtotal * 0.9;
    return subtotal;
  }
};

class ReceiptPrinter {
public:
  void print_receipt(Cart& cart, Catalog& catalog, Checkout& checkout) {
    std::cout << "---- Receipt ----\n";
    for (size_t i=0;i<cart.cart_ids.size();++i) {
      Product* p = catalog.find_product(cart.cart_ids[i]);
      if (!p) continue;
      std::cout << p->name << " x" << cart.cart_qty[i] << " @ " << p->price
                << " = " << (p->price * cart.cart_qty[i]) << "\n";
    }
    double subtotal = checkout.compute_subtotal(cart, catalog);
    double after_discount = checkout.apply_discounts(subtotal);
    double tax = after_discount * checkout.TAX_RATE;
    double total = after_discount + tax;
    std::cout << "Subtotal: " << subtotal << "\n";
    std::cout << "Discounted: " << after_discount << "\n";
    std::cout << "Tax: " << tax << "\n";
    std::cout << "Total: " << total << "\n";
  }
};

int main() {
  Catalog catalog;
  catalog.load_catalog();

  Cart cart;
  cart.add_to_cart(1, 4);   // 4 apples
  cart.add_to_cart(2, 1);   // 1 bread
  cart.add_to_cart(4, 3);   // 3 chocolate

  Checkout checkout;
  ReceiptPrinter printer;
  printer.print_receipt(cart, catalog, checkout);

  return 0;
}