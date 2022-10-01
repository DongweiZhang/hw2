#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string prodName, double price, int qty,
                   const std::string size, const std::string brand): Product(category, prodName, price, qty ), size_(size), brand_(brand){}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keys;
    std::set<std::string> brandKeys =  parseStringToWords(brand_);
    for (std::string key : brandKeys) {
        keys.insert(key);
    }

    std::set<std::string> nameKeys =  parseStringToWords(name_);
    for (const std::string& key : nameKeys) {
        keys.insert(key);
    }

    return keys;
}

bool Clothing::isMatch(std::vector<std::string> & searchTerms) const{
    std::set<std::string> keys = this->keywords();

    for (std::string term: searchTerms) {
        if (keys.count(term) > 0){
            return true;
        }
    }
	return false;
}

std::string Clothing::displayString() const{
    //std::string info = category_ + "\t" + name_ + "\t" +std::to_string(price_) + "\t" + std::to_string(qty_) + "\t" + size_ + "\t" + brand_;
    std::string info = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_)+ " " + std::to_string(qty_) + " " + "left.";
    return info;
}

void Clothing::dump(std::ostream& os) const{

	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ <<std::endl;
}

