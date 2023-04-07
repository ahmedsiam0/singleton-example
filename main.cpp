#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

class ExchangeRate {
    public:
    string BaseCurrency;
    string TargetCurrency;
    double Rate;

    ExchangeRate(string baseCurrency, string targetCurrency, double rate) {
        BaseCurrency = baseCurrency;
        TargetCurrency = targetCurrency;
        Rate = rate;
    }

    bool operator==(const ExchangeRate &second) {
        if(BaseCurrency == second.BaseCurrency && TargetCurrency == second.TargetCurrency) {
            return true;
        }
        return false;
    }
};

class CurrencyConverter {
    private:
    vector<ExchangeRate> _exchangeRate;
    void LoadExchangeRates() {
        this_thread::sleep_for(std::chrono::milliseconds(3000));
        
        _exchangeRate = {
            ExchangeRate("USD", "SAR", 3.75),
            ExchangeRate("USD", "EGP", 30.60),
            ExchangeRate("SAR", "EGP", 8.16)
        };
    }
    CurrencyConverter() {
        LoadExchangeRates();
    }
    public:

    CurrencyConverter(CurrencyConverter &other) = delete;
    void operator=(const CurrencyConverter &) = delete;

    static CurrencyConverter& getInstance() {
        static CurrencyConverter instance;
        return instance;
    }
    
    double Convert(string baseCurrency, string targetCurrency, double amount) {
        auto exchange = find(_exchangeRate.begin(), _exchangeRate.end(), ExchangeRate(baseCurrency, targetCurrency, 0));
        return amount * _exchangeRate[exchange - _exchangeRate.begin()].Rate;
    }
};

int main() {
    string baseCurrency, targetCurrency;
    double amount, exchangedAmount;

    while (true) {
        cout << "Enter base currency: ";
        cin >> baseCurrency;
        cout << "Enter target currency: ";
        cin >> targetCurrency;
        cout << "Enter amount: ";
        cin >> amount;

        //CurrencyConverter converter;
        auto exchangedAmount =
            CurrencyConverter::getInstance().Convert(baseCurrency, targetCurrency, amount);

        cout << "Sum: " << exchangedAmount << endl;
        cout << "----------------------------------\n";
    }
}
