#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char isbn[20], title[50], author[30];
    double base_price;

    void copy(const Book &b) {
        strcpy(isbn, b.isbn);
        strcpy(title, b.title);
        strcpy(author, b.author);
        base_price = b.base_price;
    }
public:
    Book(char *isbn = "", char *title = "", char *author = "", double base_price = 0) {
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->base_price = base_price;
    }

    Book(const Book &b) {
        copy(b);
    }

    virtual double price() = 0;
    virtual bool operator >(Book &b) = 0;
    friend ostream &operator <<(ostream &os, Book &b);
    virtual ~Book(){};
};

ostream &operator <<(ostream &os, Book &b) {
    os << b.isbn << ": " << b.title << ", " << b.author << " " << b.price() << endl;
    return os;
}

class OnlineBook : public Book {
private:
    char *url;
    int size;

    void copy(const OnlineBook &ob) {
        url = new char[strlen(ob.url) + 1];
        strcpy(url, ob.url);
        size = ob.size;
    }
public:
    OnlineBook(char *isbn = "", char *title = "", char *author = "",
               double base_price = 0, char *url = "", int size = 0) : Book(isbn, title, author, base_price) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->size = size;
    }

    OnlineBook(const OnlineBook &ob) : Book(ob) {
        copy(ob);
    }

    double price() {
        if (size > 20) return base_price + (base_price * 0.2);
        else return base_price;
    }

    bool operator>(Book &b) {
        if (this->price() > b.price()) return true;
        else return false;
    }

    void setISBN(char *isbn) {
        strcpy(this->isbn, isbn);
    }

    OnlineBook& operator=(const OnlineBook& ob) {
        if (this != &ob) {
            Book::copy(ob);
            delete[] url;
            url = new char[strlen(ob.url) + 1];
            strcpy(url, ob.url);
            size = ob.size;
        }
        return *this;
    }

    friend ostream &operator <<(ostream &os, OnlineBook &ob);

    ~OnlineBook() {delete [] url;}
};

ostream &operator <<(ostream &os, OnlineBook &ob) {
    os << ob.isbn << ": " << ob.title << ", " << ob.author << " " << ob.price() << endl;
    return os;
}

class PrintBook : public Book {
private:
    double weight;
    bool inStock;
public:
    PrintBook(char *isbn = "", char *title = "", char *author = "",
         double base_price = 0, double weight = 0, bool inStock = false) : Book(isbn, title, author, base_price) {
        this->weight = weight;
        this->inStock = inStock;
    }

    double price() {
        if (weight > 0.7) return base_price + (base_price * 0.15);
        else return base_price;
    }

    bool operator >(Book &b) {
        if (this->price() > b.price()) return true;
        else return false;
    }

    friend ostream &operator <<(ostream &os, PrintBook &pb);

    ~PrintBook() {}
};

void mostExpensiveBook(Book **books, int n);

ostream &operator <<(ostream &os, PrintBook &pb) {
    os << pb.isbn << ": " << pb.title << ", " << pb.author << " " << pb.price() << endl;
    return os;
}

void mostExpensiveBook(Book **books, int n) {
    cout << "FINKI-Education" << endl;

    int online_count = 0, print_count = 0;
    Book* max_price = books[0];

    for (int i = 0; i < n; i++) {
        if (dynamic_cast<OnlineBook*>(books[i])) online_count++;
        else print_count++;

        if(*books[i] > *max_price) max_price = books[i];
    }

    cout << "Total number of online books: " << online_count << endl;
    cout << "Total number of print books: " << print_count << endl;
    cout << "The most expensive book is: " << endl << *max_price << endl;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}