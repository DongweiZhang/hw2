#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string prodName, double price, int qty,
           const std::string isbn,const std::string author) : Product(category, prodName, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys;
    keys.insert(convToLower(isbn_));

    std::set<std::string> authorKeys =  parseStringToWords(author_);
    for (std::string key : authorKeys) {
        keys.insert(key);
    }

    return keys;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    // todo
    return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const {
    std::string info = category_ + "\t" + name_ + "\t" + std::to_string(price_) + "\t" + std::to_string(qty_) + "\t" + isbn_ + "\t" + author_;
    return info;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

