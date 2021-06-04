#include <iostream>
#include <fstream>
#include <string.h>

#include "queue.h"

using namespace std;

typedef unsigned int uint;

struct SShopItem {
    uint count;
    uint buyPrice;
};

typedef SQueue<SShopItem> SCart;

void generateCart(SCart* cart) {
    ifstream ifs("./input2.txt");

    if (!ifs.is_open()) {
        cout << "no input file found: expected filename \"input2.txt\"" << endl;

        return;
    }

    string str;
    string del = ">";

    while (getline(ifs, str)) {
        SShopItem item;

        uint count, price;
        try {
            string chislo1 = str.substr(0, str.find(del));
            str = str.substr(str.find(del) + 1);

            string chislo2 = str.substr(0, str.find(del));
            str = str.substr(str.find(del) + 1);
        
            count = stoi(chislo1);
            price = stoi(chislo2);
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

        item.count = count;
        item.buyPrice = price;

        cart->push(item);
    }
}

int main() {
    SCart cart;
    
    generateCart(&cart);
    
    uint totalMarja = 0;

    char c;
    bool bWork = true;
    while ( bWork ) {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "(a)dd/(b)uy/(i)nfo/(e)xit" << endl;
        cout << "> ";
        cin >> c;

        cout << "____________________________________________" << endl;

        switch ( c ) {
        case 'a': {
            cout << "Enter capacity and buy price" << endl;
            uint count;
            uint buyPrice;

            cin >> count >> buyPrice;

            SShopItem item;
            item.count = count;
            item.buyPrice = buyPrice;

            cart.push( item );
        }
        break;

        case 'b': {
            if ( cart.length() == 0 ) {
                cout << "Cart is empty!" << endl;
                break;
            }

            cout << "Enter count of items and price" << endl;
            uint count;
            uint price;
            cin >> count >> price;

            SCart temp;

            while ( count > 0 ) {
                if ( cart.length() == 0 ) {
                    cout << "Cart is empty at buy time!" << endl;
                    break;
                }

                SShopItem item = cart.pop();
                if ( price < item.buyPrice ) {
                    temp.push( item );
                    continue;
                }

                if ( item.count == count ) {
                    totalMarja += item.buyPrice * item.count;
                    count = 0;
                } else {
                    if ( item.count < count ) {
                        count -= item.count;
                        totalMarja += item.buyPrice * item.count;
                    } else {
                        totalMarja += item.buyPrice * count;
                        item.count -= count;
                        count = 0;
                        temp.push( item );
                    }
                }
            }

            while ( temp.length() > 0 ) {
                cart.push( temp.pop() );
            }
        }
        break;

        case 'i': {
            cout << "Info:" << endl;
            uint tcount = 0;
            uint tprice = 0;

            SCart temp;

            while ( cart.length() > 0 ) {
                SShopItem item = cart.pop();
                tcount += item.count;
                tprice += item.count * item.buyPrice;

                temp.push( item );
            }

            while ( temp.length() > 0 ) {
                cart.push( temp.pop() );
            }

            cout << "Total count: " << tcount << endl;
            cout << "Total price: " << tprice << endl;
            cout << "Total marja: " << totalMarja << endl;
        }
        break;

        case 'e':
            bWork = false;
            break;

        default:
            cout << "Entered invalid pattern!" << endl;
            break;
        }

        c = ' ';
        cout << "____________________________________________" << endl;
    }
    return 0;
}
