#ifndef HW2_MOVIE_H
#define HW2_MOVIE_H
/**
 * Implement all functions and properties of movies
 *  Movie's constructor and deconstructor
 *  Movies' information and display method
 */
#include "product.h"

class Movie : public Product{

public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);

    ~Movie();

    std::set<std::string> keywords() const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
    std::set<std::string> keywords_;
};

#endif //HW2_MOVIE_H