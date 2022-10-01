#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string prodName, double price, int qty,
             const std::string genre, const std::string rating): Product(category, prodName, price, qty ), genre_(genre), rating_(rating){}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keys;
    keys.insert(convToLower(genre_));

    std::set<std::string> nameKeys =  parseStringToWords(name_);
    for (const std::string& key : nameKeys) {
        keys.insert(key);
    }

    return keys;
}

bool Movie::isMatch(std::vector<std::string> & searchTerms) const{
    std::set<std::string> keys = this->keywords();

    for (std::string term: searchTerms) {
        if (keys.count(term) > 0){
            return true;
        }
    }
	return false;
}

std::string Movie::displayString() const{
    //std::string info = category_ + "\t" +name_ + "\t" +std::to_string(price_) + "\t" + std::to_string(qty_) + "\t" + genre_ + "\t" + rating_;
    std::string info = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_)+ " " + std::to_string(qty_) + " " + "left.";
    return info;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

