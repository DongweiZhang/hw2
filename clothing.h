#ifndef HW2_CLOTHING_H
#define HW2_CLOTHING_H

/**
 * Implement all functions and properties of clothings
 *  Clothing's constructor and deconstructor
 *  Clothings' information and display method
 */

#include "product.h"

class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);

    ~Clothing();

    std::set<std::string> keywords() const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
    std::set<std::string> keywords_;


};

#endif //HW2_CLOTHING_H