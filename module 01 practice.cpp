#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Базовый класс транспортное средство
class Vehicle {
protected:
    string brand;
    string model;
    int year;

public:
    Vehicle(const string& brand, const string& model, int year)
        : brand(brand), model(model), year(year) {}

    virtual ~Vehicle() = default;

    virtual void start() const {
        cout << brand << " " << model << " (год: " << year << ") двигатель запущен." << endl;
    }

    virtual void stop() const {
        cout << brand << " " << model << " (год: " << year << ") двигатель остановлен." << endl;
    }

    virtual void showInfo() const {
        cout << "Марка: " << brand << ", Модель: " << model << ", Год выпуска: " << year << endl;
    }
};

// Производный класс автомобиль
class Car : public Vehicle {
private:
    int doors;
    string gearbox;

public:
    Car(const string& brand, const string& model, int year, int doors, const string& gearbox)
        : Vehicle(brand, model, year), doors(doors), gearbox(gearbox) {}

    void showInfo() const override {
        Vehicle::showInfo();
        cout << "Двери: " << doors << ", Коробка передач: " << gearbox << endl;
    }
};

// Производный класс мотоцикл
class Motorcycle : public Vehicle {
private:
    string type;
    bool box;

public:
    Motorcycle(const string& brand, const string& model, int year, const string& type, bool box)
        : Vehicle(brand, model, year), type(type), box(box) {}

    void showInfo() const override {
        Vehicle::showInfo();
        cout << "Тип: " << type << ", Бокс: " << (box ? "Есть" : "Нет") << endl;
    }
};

// Класс гараж
class Garage {
private:
    vector<shared_ptr<Vehicle>> vehicles;

public:
    void add(const shared_ptr<Vehicle>& vehicle) {
        vehicles.push_back(vehicle);
    }

    void remove(int index) {
        if (index >= 0 && index < vehicles.size()) {
            vehicles.erase(vehicles.begin() + index);
            cout << "Транспортное средство удалено из гаража." << endl;
        } else {
            cout << "Неверный индекс." << endl;
        }
    }

    void showAll() const {
        cout << "Транспортные средства в гараже:" << endl;
        for (const auto& vehicle : vehicles) {
            vehicle->showInfo();
            cout << endl;
        }
    }
};

// Класс автопарк
class Fleet {
private:
    vector<shared_ptr<Garage>> garages;

public:
    void addGarage(const shared_ptr<Garage>& garage) {
        garages.push_back(garage);
    }

    void removeGarage(int index) {
        if (index >= 0 && index < garages.size()) {
            garages.erase(garages.begin() + index);
            cout << "Гараж удалён из автопарка." << endl;
        } else {
            cout << "Неверный индекс." << endl;
        }
    }

    void showAllVehicles() const {
        cout << "Поиск транспортных средств во всех гаражах:" << endl;
        for (const auto& garage : garages) {
            garage->showAll();
        }
    }
};

// Функция для тестирования
void testApp() {
    // Создание транспортных средств
    shared_ptr<Vehicle> car1 = make_shared<Car>("Toyota", "Camry", 2021, 4, "Автомат");
    shared_ptr<Vehicle> car2 = make_shared<Car>("Honda", "Civic", 2020, 4, "Механика");
    shared_ptr<Vehicle> moto1 = make_shared<Motorcycle>("Yamaha", "R1", 2019, "Спортбайк", true);

    // Создание гаражей
    shared_ptr<Garage> garage1 = make_shared<Garage>();
    shared_ptr<Garage> garage2 = make_shared<Garage>();

    // Добавление транспорта в гаражи
    garage1->add(car1);
    garage1->add(moto1);
    garage2->add(car2);

    // Создание автопарка и добавление гаражей
    Fleet fleet;
    fleet.addGarage(garage1);
    fleet.addGarage(garage2);

    // Отображение всего транспорта
    fleet.showAllVehicles();

    // Удаление транспортам и гаража
    garage1->remove(1); // Удаление мотоцикла из гаража 1
    fleet.removeGarage(1); // Удаление гаража 2
}

int main() {
    testApp();
    return 0;
}

