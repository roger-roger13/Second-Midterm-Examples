#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here

enum Size {
    SMALL, LARGE, FAMILY
};

class Pizza {
protected:
    char name[20], ingredients[100];
    float base_price;
public:
    Pizza(char *name, char *ingredients, float base_price) : base_price(base_price) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    bool operator<(Pizza &p) {
        return price() < p.price();
    }
    virtual float price() const = 0;
    virtual ~Pizza() {}
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza(char *name, char *ingredients, float base_price, Size size = SMALL) : Pizza(name, ingredients, base_price), size(size) {}

    float price() const override {
        return (size == SMALL) ? base_price * 1.1 : (size == LARGE) ? base_price * 1.2 : (size == FAMILY) ? base_price * 1.3 : base_price;
    }

    friend ostream &operator<<(ostream &os, FlatPizza &fp) {
        os << fp.name << ": " << fp.ingredients << ", ";
        switch (fp.size) {
            case SMALL: os << "small - "; break;
            case LARGE: os << "large - "; break;
            case FAMILY: os << "family - "; break;
        }
        os << fp.price() << endl;
        return os;
    }

    ~FlatPizza() {}
};

class FoldedPizza : public Pizza {
private:
    bool white_flour = true;
public:
    FoldedPizza(char *name, char *ingredients, float base_price) : Pizza(name, ingredients, base_price) {}

    void setWhiteFlour(bool white_flour) {
        this->white_flour = white_flour;
    }

    float price() const override {
        return (white_flour) ? base_price + (base_price * 0.1) : base_price + (base_price * 0.3);
    }

    friend ostream &operator<<(ostream &os, FoldedPizza &fp) {
        os << fp.name << ": " << fp.ingredients << ", ";
        (fp.white_flour) ? os << "wf - " : os << "nwf - ";
        os << fp.price() << endl;
        return os;
    }

    ~FoldedPizza() {}
};

ostream &operator<<(ostream &os, Pizza &p) {
    if (dynamic_cast<FlatPizza *>(&p)) return os << *dynamic_cast<FlatPizza *>(&p);
    else return os << *dynamic_cast<FoldedPizza *>(&p);
}

void expensivePizza(Pizza** pizzas, int num) {
    Pizza *max_pizza = pizzas[0];
    for (int i = 1; i < num; i++)if(*max_pizza < *pizzas[i]) max_pizza = pizzas[i];
    cout << *max_pizza;
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
