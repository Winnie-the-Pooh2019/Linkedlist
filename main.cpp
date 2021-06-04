#include <iostream>
#include <fstream>
#include <string.h>

#include "stack.h"
#include "queue.h"

using namespace std;

struct SShopItem {
    const char* name;
    float weight;
    uint capacity;
    uint size;
};

typedef SStack<SShopItem> SCart;

void generateCart(SCart* cart) {
    ifstream ifs("./input.txt");

    if (!ifs.is_open()) {
        cout << "no input file found: expected filename \"input.txt\"" << endl;

        return;
    }

    string str;
    string del = ">";

    while (getline(ifs, str)) {
        SShopItem item;

        string name = str.substr(0, str.find(del));
        str = str.substr(str.find(del) + 1);

        string chislo = str.substr(0, str.find(del));
        str = str.substr(str.find(del) + 1);

        string chislo1 = str.substr(0, str.find(del));
        str = str.substr(str.find(del) + 1);

        string chislo2 = str.substr(0, str.find(del));
        str = str.substr(str.find(del) + 1);

        // cout  << "!!! name = " << name << " w = " << chislo
        // << " cap = " << chislo1 << " size = " << chislo2 << endl;

        float weight, cap, size;
        try {
            weight = stod(chislo);
            cap = stoi(chislo1);
            size = stoi(chislo2);
        } catch (...) {
            cout << "\ninvalid input file structure\n"
            << "do u want to get filling file tutorial? YES - y; NO - n\n" << endl;

            char c;
            cin >> c;

            if (c == 'y') {
                cout << "\nevery single number gets place in its own line"
                << "there sould be no spaces or other simbols besides"
                << "digits or dots\n" << endl;
            }
        }

        item.name = strndup(name.c_str(), name.length());
        item.weight = weight;
        item.capacity = cap;
        item.size = size;

        cart->push(item);
    }
}

int main() {
    cout << "--- Task 1\n\n";

    SStack<SShopItem> cart;
    generateCart(&cart);

    char a;
    bool cyrcle = true;
    while (cyrcle) {
        cout << "--- choose what do u want to do: add, pop or clean a cart OR EXIT OR SHOW CART: a/p/c/s/e\n";

        cin >> a;

        SShopItem item;
        switch (a)
        {
            case 'a': {
                cout << "--- input name, weight, capacity and size of an item:\n";
                string name;
                float w;
                uint c, s;

                cin >> name >> w >> c >> s;

                item = {strndup(name.c_str(), name.length()), w, c, s};

                cart.push(item);

                cout << "--- item is added\n";
            }
            break;

            case 'p': {
                cout << "--- input name, weight, capacity and size of an item:\n";

                string name;
                float w;
                uint c, s;

                cin >> name >> w >> c >> s;

                item = {name.c_str(), w, c, s};

                SStack<SShopItem> temp;
                SShopItem tempItem;
                string strin = "";

                do {
                    tempItem = cart.pop();

                    if (strcmp(item.name, tempItem.name) == 0 &&
                    item.weight == tempItem.weight &&
                    item.capacity == tempItem.capacity &&
                    item.size == tempItem.size) {
                        strin = "--- item is found\n";
                        break;
                    }

                    temp.push( tempItem );
                } while (cart.length() != 0);

                while ( temp.length() != 0 ) {
                    cart.push( temp.pop() );
                }

                if (strin == "") {
                    strin = "--- no such item\n";
                }

                cout << strin;
            }
            break;

            case 'c': {
                while(cart.length() != 0) {
                    cart.pop();
                } 

                cout << "--- cart is cleaned\n";
            }
            break;

            case 's': {
                SCart temp;
                SShopItem titem;
                while ( cart.length() != 0 ) {
                    titem = cart.pop();
                    cout << titem.name << " " << titem.weight << " " << titem.capacity << " " << titem.size << endl;
                    temp.push( titem );
                }

                while ( temp.length() != 0 ) {
                    cart.push( temp.pop() );
                }
            }
            break;

            case 'e':
                cyrcle = false;
                break;

            default:
                cout << "--- incorrect input\n";
                break;
        }
    }

    return 0;
}
