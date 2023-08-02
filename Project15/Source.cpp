#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <string.h>
#include<fstream>
#include<sstream>


using namespace std;

static int countMesage = 0;

class Ingredient {
public:
    string name;
    int quantity;
    Ingredient()
    {

    }
    Ingredient(string n, int q) : name(n), quantity(q) {}

};


class ErrorLogger {
public:
    static void logError(const string& errorMessage) {
        ofstream file("error_log.txt", ios::app); 
        if (file.is_open()) {
            file << errorMessage << endl;
            file.close();
        }
    }
};

void someFunction() {

    try {
      
        throw runtime_error("Some error occurred");
    }
    catch (const exception& ex) {
        ErrorLogger::logError("Error in someFunction(): " + string(ex.what()));
    }
}


class Meal {
public:
    string name;
    string details;
    double price;
    double rating = 0;
    int calories; 
    double energy; 
    Meal()
    {

    }
    Meal(string n, string d, double p, int cal, double en)
        : name(n), details(d), price(p), rating(0), calories(cal), energy(en) {}
    

};

class Kitchen {
public:
    vector<string> orders;
    std::vector<std::string> acceptedOrders;
    std::vector<std::string> rejectedOrders;



    void notifyOrder(string tableNumber, string mealName) {
        string order = "Stol " + tableNumber + " ucun " + mealName + " yemeyi siparis edildi.";
        orders.push_back(order);
        cout << order << endl;
        someFunction();
    }

    const std::vector<std::string>& getAcceptedOrders() const {
        return acceptedOrders;
    }

    const std::vector<std::string>& getRejectedOrders() const {
        return rejectedOrders;
    }

    void viewOrders() {
        cout << "Siparisler :" << endl;
        for (const string& order : orders) {
            cout << order << endl;
        }
        cout << endl;
    }

    void acceptOrder(string mealName) {
        cout << mealName << " yemeyi qebul edildi ." << endl;
        acceptedOrders.push_back("siparis qebul edildi ! " + mealName);
            countMesage++;

    }

    void printAndClearAcceptedOrders() {
        for (const string& acceptedOrder : acceptedOrders) {
            cout << acceptedOrder << endl;
        }
        acceptedOrders.clear();
        if (countMesage> 0)
        {
        countMesage--;

        }
    }



    void rejectOrder(string mealName, string reason) {
        cout << mealName << " yemeyi reddedildi. Sebeb: " << reason << endl;
        rejectedOrders.push_back(mealName + "Yemey reddedildi , Sebeb: " + reason);
            countMesage++;
       
    }

    void printAndClearRejectedOrders() {
        for (const string& rejectedOrder : rejectedOrders) {
            cout << rejectedOrder << endl;
        }
        rejectedOrders.clear();
        if (countMesage > 0)
        {
            countMesage--;

        }
    }

};

class Stock {
public:
    map<string, Ingredient> ingredients;

    void viewIngredients() {
        cout << "All Ingredients :" << endl;
        for (const auto& pair : ingredients) {
            cout << pair.first << " - " << pair.second.quantity << " adet" << endl;
        }
        cout << endl;
    }

    void addIngredient(string name, int quantity) {
        ingredients[name] = Ingredient(name, quantity);
    }


    void increaseIngredientQuantity(const string& name, int quantityToAdd) {
        auto it = ingredients.find(name);
        if (it != ingredients.end()) {
            it->second.quantity += quantityToAdd;
            cout << "Increased " << name << " quantity by " << quantityToAdd << "." << endl;
        }
        else {
            cout << name << " ingredient bulunamadi." << endl;
        }
    }

    void decreaseIngredientQuantity(const string& name, int quantityToRemove) {
        auto it = ingredients.find(name);
        if (it != ingredients.end()) {
            if (it->second.quantity >= quantityToRemove) {
                it->second.quantity -= quantityToRemove;
                cout << "Azaldildi " << name << " miqdar  " << quantityToRemove << "." << endl;
            }
            else {
                cout << "Not enough " << name << " in stock. Current quantity: " << it->second.quantity << endl;
            }
        }
        else {
            cout << name << " ingredient bulunamadi." << endl;
        }
    }




    void removeIngredient(string name) {
      
        ingredients.erase(name);
        cout << name << " ingredient silindi." << endl;
    }

    void updateIngredientQuantity(string name, int quantity) {
        ingredients[name].quantity = quantity;
        cout << name << " ingredientin miqdari update oldu ." << endl;

    }
    bool checkIfIngredientAvailable(const string& name, int quantity) {
        auto it = ingredients.find(name);
        if (it != ingredients.end() && it->second.quantity >= quantity) {
            return true;
        }
        return false;
    }

private:
    const string filename = "ingredient.txt";

    void loadIngredientsFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string name;
            int quantity;
            while (file >> name >> quantity) {
                ingredients[name] = Ingredient(name, quantity);
            }
            file.close();
        }
    }

    void saveIngredientsToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : ingredients) {
                file << pair.first << " " << pair.second.quantity << endl;
            }
            file.close();
        }
    }

};

class Client {
private:
    map<string, int> selectedIngredients;

public:
    string tableNumber;
    Kitchen* kitchen;
    Stock* stock;

    Client() = default;


    Client(string & tablenumber ): kitchen(nullptr) , stock(nullptr)
    {
        SetTableNumber(tablenumber);
    }

    void SetTableNumber(string& tablenumber) {
        if (tablenumber!=tableNumber)
        {
            this->tableNumber = tablenumber;
            someFunction();

        }
        else if(tablenumber==tableNumber){
            cout << "Secdiyiniz masa doludur " << endl;
            system("pause");
            system("cls");
           
        }
        else if (tablenumber.empty())
        {
            cout << "Masa nomreniz daxil etmek lazimdir ...     " << endl;
            system("pause");
            system("cls");

        }


    }

        void placeOrder(Meal& meal) {
        cout << "Siparis verilen yemek: " << meal.name << endl;

        kitchen->notifyOrder(tableNumber, meal.name);
         Message(*kitchen, meal.name);

    }

        void Message(Kitchen& kitchen, const string& orderedMealName) {
            for (const string& order : kitchen.orders) {
                if (order.find("Table " + tableNumber + " ucun  " + orderedMealName + " yemeyi  siparis edildi.") != string::npos) {
                    cout << "siparis qebul edildi, " << orderedMealName << " yemek hazirlanir." << endl;
                    return;
                }
                else if (order.find("Table " + tableNumber + " ucun " + orderedMealName + " yemeyi  qebul olunmadi ! . Sebeb : ") != string::npos) {
                    cout << "Teessuf ki , " << orderedMealName << "Yemek qebul edilmedi ,  Sebep: " << order.substr(order.find("Sebep: ") + 7) << endl;
                    return;
                }
            }
        }


    void viewSelectedIngredients() {
        cout << "Secilen ingredient:" << endl;
        for (const auto& pair : selectedIngredients) {
            cout << pair.first << " - " << pair.second << " adet" << endl;
        }
        cout << endl;
    }



    void selectIngredientFromStock(Stock& stock, const string& ingredientName, int quantity) {
        auto it = stock.ingredients.find(ingredientName);
        if (it != stock.ingredients.end()) {
            if (it->second.quantity >= quantity) {
                selectedIngredients[ingredientName] = quantity;
                it->second.quantity -= quantity;
                cout << quantity << " dene " << ingredientName << " secildi." << endl;
            }
            else {
                cout << "Stokta kifayet miqdarda " << ingredientName << " tapilmir." << endl;
            }
        }
        else {
            cout << ingredientName << " ingredient stokta tapilmir ." << endl;
        }
    }



    void viewMenu(vector<Meal>& menu) {
        cout << "MENU" << endl;
        for (const Meal& meal : menu) {
            cout << meal.name << " - " << meal.price << " $" << endl;
        }
        cout << endl;
    }

    void viewMealDetails(Meal& meal) {
        cout << "Yemek Adi: " << meal.name << endl;
        cout << "Detaylar: " << meal.details << endl;
        cout << "Qiymet : " << meal.price << " $" << endl;
        cout << "Deyerlendirme : " << meal.rating << "/5" << endl;
    }



    void rateMeal(Meal& meal, double rating) {
        meal.rating = rating;
        cout << "Yemek deyerdirilmesi  edildi ." << endl;
      
    }

    Meal* searchMeal(vector<Meal>& menu, const string& mealName) {
        for (auto& meal : menu) {
            if (meal.name == mealName) {
                return &meal; 
            }
        }
        return nullptr; 
    }

 

};

class Restaurant {
public:
    string name;
    string address;
    string city;
    double budget;
    vector<Meal> menu;
    Kitchen kitchen;
    Stock stock;

    Restaurant(string n, string addr, string c) : name(n), address(addr), city(c), budget(0) {}

    void addMealToMenu(Meal meal) {
        menu.push_back(meal);
    }

    void viewMenu() {
        cout << "MENU" << endl;
        for (const Meal& meal : menu) {
            cout << meal.name << " - " << meal.price << " $" << endl;
        }
        cout << endl;
    }
    void updateMeal(const string& mealName, const string& newDetails, double newPrice) {
        for (auto& meal : menu) {
            if (meal.name == mealName) {
                meal.details = newDetails;
                meal.price = newPrice;
                cout << mealName << " is updated in the menu." << endl;
                return;
            }
        }
        cout << mealName << " is not found in the menu." << endl;
    }
  

    void deleteMeal(const string& mealName) {
        for (auto it = menu.begin(); it != menu.end(); ++it) {
            if (it->name == mealName) {
                menu.erase(it);
                cout << mealName << " is removed from the menu." << endl;
                return;
            }
        }
        cout << mealName << " is not found in the menu." << endl;
    }

};

class Admin {
private:

    string username = "salam";
    string password = "123";
    string GetPassword()const {
        return password;
    }
public:


    string GetUserName()const {
        return username;
    }

    bool Trfls = true;


    void Yoxlamaq(string u, string p) {


        if (GetPassword() == p && GetUserName() == u)
        {
            cout << "Welcome Admin " << endl;


        }
        else {
            cout << "Username or Password Yanlisdir " << endl << endl;
            Trfls = false;
        }
    }
};


void main() {
    Kitchen kitchen;
    Stock stock;
    Restaurant restaurant("salam", "baku", "a");
    Meal meal1("Spageti", "Classic Italian dis", 15.99, 600, 5000);
    Meal meal2("Kabab", "Classic Azerbaijan dis", 18.50, 700, 25000);
    Meal meal3("YumurtaPomidor ", "Classic morning  dis", 5.00, 300, 15000);
    restaurant.addMealToMenu(meal1);
    restaurant.addMealToMenu(meal2);
    restaurant.addMealToMenu(meal3);
    stock.addIngredient("Pomidor", 0.5);
    stock.addIngredient("Barbeku Sous", 0.75);
    stock.addIngredient("Salsa sous", 0.75);
    stock.addIngredient("Can eti", 5);
    stock.addIngredient("Xiyar Tursusu", 2);
    

    

    system("color 7");
    while (true)
    {
        cout << "1.Admin\t" << "2.Client " << endl;
        int secim = 0;
        cin >> secim;
        system("cls");
        Client client;
        while (true)
        {


            if (secim == 1)
            {
                cout << "1.Back " << endl << "2.Davam etmek " << endl;
                int secimBac = 0;
                cin >> secimBac;
                if (secimBac==1)
                {
                    cout << "Back olunur .." << endl;
                    system("pause");
                    system("cls");
                    break;

                }
                Admin admin;
                string user;
                cout << "Admin Username : ";
                cin >> user;
                cout << endl;
                string pas;
                cout << "Admin Password: ";
                cin >> pas;
                admin.Yoxlamaq(user, pas);

                cout << endl;
                while (true)
                {


                    if (admin.Trfls)
                    {
                        system("pause");
                        system("cls");
                        cout << "1.Kitchen\t" << "2.Stock " << endl;
                        int secAd = 0;
                        cout << "Seciminizi edin : " << endl;
                        cin >> secAd;
                        if (secAd == 1)
                        {
                            cout << "Metbexe xow geldiniz ! " << endl;
                            system("pause");
                            system("cls");
                            //Kitchen kitchen;
                            cout << "1.All Orders\t " << endl << "2.Siparisi qebul etmek" << endl << "3.Siparisi legv etmek" <<
                                endl << "4.Restorantda yemekler " << endl << "5.Stock baxis " << endl << "6.Yemek elave et" <<
                                endl << "7.Yemek update et " << endl << "8.Yemek sil " << endl << "9.Back" << endl;
                                
                            cout << "Seciminizi edin " << endl;
                            int Kitchensecimi = 0;
                            cin >> Kitchensecimi;
                            if (Kitchensecimi == 1)
                            {
                                kitchen.viewOrders();
                            }
                            else if (Kitchensecimi == 2) {
                                string accep;
                                cout << "Qebul edeceyiniz siparisin adini qeyd edin " << endl;
                                cin.ignore();
                                getline(cin, accep);

                                kitchen.acceptOrder(accep);
                                system("pause");
                                system("cls");
                            }
                            else if (Kitchensecimi == 3) {
                                cout << "Legv olunacaq Table nomresini qeyd edin     " << endl;
                                string tablenoaccep;
                                cin.ignore();
                                getline(cin, tablenoaccep);

                                string noaccep;
                                cout << "Legv edeceyiniz siparisin adini qeyd edin   " << endl;
                                cin.ignore();
                                getline(cin, noaccep);
                                kitchen.rejectOrder(tablenoaccep, noaccep);
                                system("pause");
                                system("cls");

                            }
                            else if (Kitchensecimi == 4) {
                                restaurant.viewMenu();
                                system("pause");
                                system("cls");

                            }
                            else if (Kitchensecimi == 5)
                            {
                                stock.viewIngredients();
                                system("pause");
                                system("cls");

                            }
                       
                            else if (Kitchensecimi == 6 )
                            {
                                string mealname;
                                cout << "Yemeyin adini yazin:    " << endl;
                                cin >> mealname;

                                string detail;
                                cout << "Yemeyin detali elave edin " << endl;
                                cin >> detail;

                                double price = 0.0;

                                cout << "Yemeyin qiymetini elave edin " << endl;
                                cin >> price;

                                double calori;
                                cout << "Yemeyin calorisini qeyd edin" << endl;
                                cin >> calori;

                                double energy;
                                cout << "Yemeyin energysi qeyd edin " << endl;
                                cin >> energy;
                            
                                Meal mealadd(mealname ,detail , price , calori , energy);
                                restaurant.addMealToMenu(mealadd);

                                cout << "ELAVE olundu " << endl;
                                system("pause");
                                system("cls");



                            }
                            else if (Kitchensecimi == 7) {
                                Meal mealupdate;
                                cout << "Update edeceyiniz yemeyin adi qeyd edin    " << endl;

                                string updateMeal;
                                cin >> updateMeal;
                                cout << "Yemeyin detai qeyd edin " << endl;
                                string mealDetail; 
                                cin >> mealDetail;
                                cout << " Yemeyin qiymetini qeyd edin " << endl;
                                double UpdateMealPrice;
                                cin >> UpdateMealPrice;

                                restaurant.updateMeal(updateMeal, mealDetail, UpdateMealPrice);

                                
                            }
                            else if (Kitchensecimi == 8) {
                                string mealname; 
                                cout << "Delete edeceyiniz yemeyin adini qeyd edi n" << endl;
                                cin >> mealname;


                                restaurant.deleteMeal(mealname);

                            }
                            else if (Kitchensecimi == 9) {
                                cout << "Geriye qayidilir .... " << endl;
                                system("pause");
                                system("cls");
                                break;

                            }
                            
                        }
                        else if (secAd == 2)
                        {
                            cout << "1.Back " << endl << "2.Davam ele" << endl;
                            int secimBacStock = 0;
                            cin >> secimBacStock;
                            if (secimBacStock == 1 )
                            {
                                cout << "Back olunur .." << endl;
                                system("pause");
                                system("cls");
                                break;

                            }
                            while (true)
                            {


                                if (secimBacStock == 2)
                                {
                                    cout << "Stocka xow geldiniz !" << endl << endl;
                                    cout << "1.All Ingredients " << endl << "2.Ingredient elave et " << endl << "3.Ingredient silmek " << endl
                                        << "4. ingredientin sayini artirmaq (+) " << endl << "5 Ingredientin sayini azaltmaq (-) " << endl << "6.Back" << endl;
                                    int secimIngredStock = 0;
                                    cout << "Seciminizi edin : " << endl;
                                    cin >> secimIngredStock;
                                    system("cls");
                                    if (secimIngredStock ==  1)
                                    {
                                        stock.viewIngredients();
                                        system("pause");
                                        system("cls");

                                    }
                                    else if (secimIngredStock == 2)
                                    {
                                        cout << "Add edecceyiniz ingredients adi qeyd edin " << endl;
                                        string stockadna;
                                        cin.ignore();
                                        getline(cin, stockadna);
                                        cout << "Ingredientin miqdari " << endl;
                                        int miqdariingred = 0; 
                                        cin >> miqdariingred;

                                        stock.addIngredient(stockadna, miqdariingred);
                                        system("cls");
                                        system("pause");

                                    }
                                    else if (secimIngredStock == 3)
                                    {
                                        cout << "silmek istediyiniz Ingredientin  adini qeyd edin :      " << endl;
                                        string deleteingred;
                                        cin.ignore();
                                        getline(cin, deleteingred);
                                        stock.removeIngredient(deleteingred);
                                        system("pause");
                                        system("cls");

                                    }
                                    else if (secimIngredStock == 4)
                                    {
                                        cout << "Sayisini artiracaginiz ingredientin adini qeyd edin :" << endl;
                                        string ingredArt;
                                        cin.ignore();
                                        getline(cin, ingredArt);
                                        int say = 0;
                                        cout << "Ne qeder artacagi miqdari yazin " << endl;
                                        cin >> say;
                                        stock.increaseIngredientQuantity(ingredArt , say    );
                                        system("pause");
                                        system("cls");


                                    }
                                    else if (secimIngredStock==5)
                                    {
                                        cout << "Sayisi azaldacaginiz ingredientin adini qeyd edin " << endl;
                                        string ingredd;
                                        cin.ignore();
                                        getline(cin, ingredd);
                                        int sayy = 0; 
                                        cout << "Ne qeder azalacagi (-) miqdari yazin " << endl;
                                        cin >> sayy;
                                        stock.decreaseIngredientQuantity(ingredd, sayy);
                                        system("pause");
                                        system("cls");
                                    }
                                    else if (secimIngredStock == 6 )
                                    {
                                        cout << "Back olunur ... " << endl;
                                        system("pause");
                                        system("cls");
                                        break;
                                    }

                                }
                            }
                            
                        }
                    }
                    else {
                        cout << "Yanlis informasiya " << endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                }

            }
            else if (secim == 2)
            {
               /* Client client;*/
                string tableN;

                cout << "****************************TM Restaurantina xos gelmisiniz ! ******************" << endl << endl;
                int backsecim = 0;
                cout << "1.Back " << endl << "2. Davam etmek " << endl;

                cin >> backsecim;
                if (backsecim == 1)
                {
                    cout << "Back olunur.. " << endl;
                    system("pause");
                    system("cls");
                    break;

                }
              
                cout << "Stol nomresini qeyd edin " << endl;
                cin.ignore();
                getline(cin, tableN);
                client.SetTableNumber(tableN);
                cout << "Masaniz secilmisdir sizin masa nomreniz :  " << tableN << endl;
                system("pause");
                system("cls");
                while (true)
                {
                    cout << "1. Butun yemekler " << endl << "2.Yemeklerin detaylari " << endl << "3.Yemek siparisi "
                        << endl << "4.Yemey axtarisi " << endl << "5.Back" << endl << "6. Rating verin " << endl << "7.Meesage" << "[ " << countMesage << "]" << endl;
                    int secimClient = 0;
                    cout << "Seciminizi edin :" << endl;
                    cin >> secimClient;
                    system("cls");


                    if (secimClient == 1)
                    {

                        restaurant.viewMenu();
                        system("pause");
                        system("cls");

                    }


                    else if (secimClient == 2)
                    {
                        cout << "Detaylarina baxmaq istediyiniz yemeyin adi : " << endl;
                        string mealNameClient;
                        cin >> mealNameClient;
                        Meal* foundMeal = client.searchMeal(restaurant.menu, mealNameClient);
                        if (foundMeal != nullptr)
                        {
                            client.viewMealDetails(*foundMeal);
                            system("pause");
                            system("cls");
                        }
                        else {
                            cout << "Yemek tapilmadi ,Duzgun yazmaginiz xais olunur " << endl;
                            system("pause");
                            system("cls");
                        }

                    }
                    else if (secimClient == 3)
                    {
                        cout << "Siparis vereceyiniz yemeyin adi :" << endl;
                        string Siparis;
                        cin >> Siparis;
                        Meal* order = client.searchMeal(restaurant.menu, Siparis);

                        if (order!=nullptr)
                        {
                            cout << "1.Ingredientler elave etmek " << endl << "2.Siparis tamamlamaq" << endl;
                            int sec = 0;
                            cin >> sec;
                            if (sec==1)
                            {
                                stock.viewIngredients();
                                cout << endl << "Seciminizi edin : " << endl;
                                string secimIngre;
                                cin.ignore();
                                getline(cin, secimIngre);
                                
                                cout << endl << "miqdar : " << endl;
                                int quant = 0; 
                                cin >> quant;

                                client.selectIngredientFromStock(stock, secimIngre ,quant  );
                                kitchen.notifyOrder(tableN, order->name);
                                system("pause");
                                system("cls");



                            }
                            else if (sec == 2) {
                                cout << "Ugurla siparisiniz qeyde alindi ! " << order->name << endl;
                                kitchen.notifyOrder(tableN, order->name);
                                client.Message(kitchen, Siparis);
                                system("pause");
                                system("cls");

                            }

                        }
                     
                        else {
                            cout << "Yemek menuda yoxdur .. " << endl;
                            system("pause");
                            system("cls");
                        }

                    }
                    else if (secimClient==4)
                    {
                        cout << "Axtarisa vereceyiniz yemeyin adi : " << endl;
                        string MealNameSearch;
                        cin.ignore();
                        getline(cin, MealNameSearch);
                        Meal * Search = client.searchMeal(restaurant.menu, MealNameSearch);
                        if (Search!=nullptr)
                        {
                            cout << MealNameSearch << " tapildi. " << endl;
                            system("pause");
                            system("cls");
                        }
                        else {
                            cout << MealNameSearch << "  Yemek tapilmadi " << endl;
                            system("pause");
                            system("cls");

                        }
                    }
                
                    else if(secimClient == 5)
                    {
                        cout << "Back olundu ..." << endl;
                        system("pause");
                        system("cls");
                        break;

                    }
                    else if (secimClient == 6)
                    {
                        cout << "Rating vereceyiniz yemeyin adi :" << endl;
                        string ratemeal1; 
                        cin.ignore();
                        getline(cin, ratemeal1);

                        Meal* foundMeal = client.searchMeal(restaurant.menu, ratemeal1);
                        if (foundMeal != nullptr) {
                            double rating;
                            cout << "Rating daxil edin (0-5): ";
                            cin >> rating;

                            if (rating >= 0 && rating <= 5) {
                                client.rateMeal(*foundMeal, rating);
                            }
                            else {
                                cout << "Yanlis reyting qiymeti. Deyerlendirme 0-5 arasinda olmalidir ! " << endl;
                                system("pause");
                                system("cls");
                            }
                        }
                        else {
                            cout << "Yemek tapilmadi. Dogru ad daxil etdiyinizden emin olun !" << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else if (secimClient == 7)
                    {
                        cout << ">> Qebul edilenler << " << endl;
                        kitchen.printAndClearAcceptedOrders();
                        cout << endl << endl;
                  
                        cout << ">> Reddedilenler <<" << endl;
                        kitchen.printAndClearRejectedOrders();
                        cout << endl;

                        system("pause");
                        system("cls");
                    }
                }
            }
            else {
                cout << "Yanlis informasiya" << endl;
                system("pause");
                system("cls");
                break;



            }
        }
    }

}