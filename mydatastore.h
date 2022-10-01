#ifndef HW2_MYDATASTORE_H
#define HW2_MYDATASTORE_H

/**
 * Implement functions for Amazon System
 *  Add Users, Products to the System
 *  Implement methods of AddCarts and BuyCarts
 */

#include "datastore.h"
#include <map>
#include <vector>
#include <queue>


class MyDataStore : public DataStore{
public:
     MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    User* getUser(std::string username);

    void addCarts(User *u, Product *p);

    std::vector<Product*> getCarts(const std::string& username);

    void buyingCarts(User *u);

private:
    std::set<Product*> andSearch(std::vector<std::string>& terms);
    std::set<Product*> orSearch(std::vector<std::string>& terms);

private:
    // product inverted index
    std::map<std::string, std::set<Product*>> invertedIndex_;

    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::queue<Product*>> carts_;
};


#endif //HW2_MYDATASTORE_H
