// Program for temperature and humidity processing
// BLiSS-VOC
// Nate Maceri

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // get choice of temperature or humidity
    cout << "Temperature or humidity?" << endl;
    cout << "1. Temperature" << endl;
    cout << "2. Humidity" << endl;
    cout << "Choice: ";
    int choice;
    cin >> choice;
    bool temp;
    if (choice == 1) {
        temp = true;
    } else if (choice == 2) {
        temp = false;
    } else {
        cout << "Enter 1 for temperature or 2 for humidity" << endl;
        exit (1);
    }
    cout << endl;

    // get data filename
    string filename;
    cout << "Enter data filename: ";
    cin >> filename;
    filename += ".txt";

    // open temperature and humidity data files
    ifstream data;
    data.open(filename);

    // check if data file opened successfully
    if (!data.is_open()) {
        cout << "Data file failed to open" << endl;
        exit(1);
    }
    cout << endl;

    // determine nominal value
    int dataCount = 0;
    double currValue = 0;
    double nominal = 0;
    string date;
    string time;
    string AM_PM;
    while (data >> date) {
        data >> time >> AM_PM >> currValue;
        nominal += currValue;
        dataCount++;
    }
    nominal = nominal / dataCount;
    cout << "Nominal: " << nominal << endl << endl;
    
    // set upper and lower bounds on nominal value
    double upper = nominal + 2;
    double lower = nominal - 2;

    // reset file input buffer
    data.clear();
    data.seekg(0);

    // determine if any data points exceed +-2 of nominal
    bool exceeded = false;
    double difference = 0;
    while (data >> date) {
        data >> time >> AM_PM >> currValue;
        AM_PM.pop_back();
        if (currValue > upper || currValue < lower) {
            difference = currValue - nominal;
            if (temp) {
                cout << "Temperature ";
            } else {
                cout << "Humidity ";
            }
            cout << "exceeded nominal value of " << nominal << " by " << difference << " at "
            << date << " " << time << " " << AM_PM << endl;
            exceeded = true;
        }
    }
    if (!exceeded) {
        if (temp) {
            cout << "Temperature ";
        } else {
            cout << "Humidity ";
        }
        cout << "did not exceed nominal value of " << nominal << endl;
    }

    return 0;
}