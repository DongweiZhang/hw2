#include "mydatastore.h"
#include "util.h"



MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){
    for (auto p : products_) {
        delete p;
    }

    for (auto u : users_) {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p) {
    if (p != nullptr) {
        products_.push_back(p);

        // update inverted index
        std::set<std::string> keys = p->keywords();
        if (!keys.empty()) {
            for (std::string key : keys) {
                invertedIndex_[key].insert(p);
            }
        }
    }
}

void MyDataStore::addUser(User* u) {
    if (u != nullptr) {
        users_.push_back(u);
        carts_[u->getName()] = std::queue<Product*>();
    }
}

std::set<Product*> MyDataStore::orSearch(std::vector<std::string>& terms) {
    std::set<Product*> ret;

    if (invertedIndex_.count(terms[0]) > 0) {
        ret = invertedIndex_[terms[0]];
    }

    for (int i = 1; i < terms.size(); ++i) {
        std::string term = terms[i];
        if (invertedIndex_.count(term) > 0) {
            std::set<Product*> tmp = invertedIndex_[term];
            ret = setUnion(ret, tmp);
        }
    }
    return ret;
}

std::set<Product*> MyDataStore::andSearch(std::vector<std::string>& terms) {
    std::set<Product*> ret;

    if (invertedIndex_.count(terms[0]) > 0) {
        ret = invertedIndex_[terms[0]];
    }

    for (int i = 1; i < terms.size(); ++i) {
        std::string term = terms[i];
        std::set<Product*> tmp;
        if (invertedIndex_.count(term) > 0) {
            tmp = invertedIndex_[term];
            ret = setIntersection(ret, tmp);
        } else {
            ret = setIntersection(ret, tmp);
        }
    }
    return ret;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> ret;

    if (terms.size() > 0) {
        std::set<Product*> products;
        if (type == 0) {
            products = andSearch(terms);
        } else {
            products = orSearch(terms);
        }
        ret.clear();
        ret.insert(ret.begin(), products.begin(), products.end());
    }

    return ret;
}

void MyDataStore::dump(std::ostream& ofile) {
    // dump products
    ofile << "<products>" << std::endl;
    for (Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    // dump users
    ofile << "<users>" << std::endl;
    for (User* u : users_) {
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

User* MyDataStore::getUser(std::string username) {
    for (auto user : users_) {
        if (user->getName() == username) {
            return user;
        }
    }
    return nullptr;
}

void MyDataStore::addCarts(User *u, Product *p){
    if (u == nullptr) return;
    if (carts_.count(u->getName()) != 0){
        carts_[u->getName()].push(p);
    }
}

std::vector<Product*> MyDataStore::getCarts(const std::string& username) {
    std::vector<Product*> ret;

    if(carts_.count(username) > 0) {
        std::queue<Product*> cart = carts_[username];
        for (int i = 0; i < cart.size(); ++i) {
            ret.push_back(cart.front());
            cart.push(cart.front());
            cart.pop();
        }
    }
    return ret;
}

void MyDataStore::buyingCarts(User *u){
    if(carts_.count(u->getName()) > 0) {
        int size = carts_[u->getName()].size();
        for (int i = 0; i < size; ++i) {
            Product *p = carts_[u->getName()].front();
            if (p->getQty() >= 1 && u->getBalance() >= p->getPrice()) {
                p->subtractQty(1);
                u->deductAmount(p->getPrice());
                carts_[u->getName()].pop();
            }
        }
    }
}