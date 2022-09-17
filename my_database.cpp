#include "my_database.h"


void MyDatabase::addProduct(Product* p) {
    // todo
}

/**
 * Adds a user to the data store
 */
void MyDatabase::addUser(User* u) {
    // todo
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDatabase::search(std::vector<std::string>& terms, int type) {
    // todo
    std::vector<Product*> ret;
    return ret;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDatabase::dump(std::ostream& ofile) {
    // todo
}