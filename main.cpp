#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool smol(int& a) {
    if (a == 0) {
        cout << "Oh no! There is no array!";
        return true;
    }
    if (a == 1) {
        cout << "Only one? It's gonna be lonely..." << endl;
        int lonelyNumber;
        cin >> lonelyNumber;
        cout << lonelyNumber * lonelyNumber;
        return true;
    }
    return false;
}

void squarification(vector<int>& values) {
    for (int & value : values) {
        value = value * value;
    }
}

void MergeSortImpl(vector<int>& values, vector<int>& buffer, int left, int right) {
    if (left < right) {
        int median = (left + right) / 2;
        MergeSortImpl(values, buffer, left, median);
        MergeSortImpl(values, buffer, median + 1, right);

        int k = left;
        for (int i = left, j = median + 1; i <= median || j <= right; ) {
            if (j > right || (i <= median && values[i] < values[j])) {
                buffer[k] = values[i];
                ++i;
            } else {
                buffer[k] = values[j];
                ++j;
            }
            ++k;
        }
        for (int i = left; i <= right; ++i) {
            values[i] = buffer[i];
        }
    }
}

void MergeSort(vector<int>& values) {
    vector<int> buffer(values.size());
    MergeSortImpl(values, buffer, 0, (int)(values.size() - 1));
}

int main() {
    cout << "Hi! I'm a program that can make every array element squared and then sort the array." << endl << "Why? Well, why not?" << endl << endl;
    cout << "Please, chose your preferable input:" << endl << "    -Console" << endl << "    -File" << endl;
    string inputPreference;
    short soWhatDoYouWant = 0;
    getline(cin, inputPreference);
    while (soWhatDoYouWant == 0) {
        if (inputPreference == "Console" || inputPreference == "console") {
            soWhatDoYouWant = 1;
            cout << "Well, here we go then!" << endl << "Input the number of elements and then the elements in the console." << endl;
        } else if (inputPreference == "File" || inputPreference == "file") {
            soWhatDoYouWant = 2;
            cout << "Create a file named Here.txt and fill in with number of elements and then the elements." << endl << "Type DONE if you've done that." << endl;
            string answer;
            cin >> answer;
            while (answer != "DONE") cin >> answer;
        } else if (inputPreference == "I don't wanna work with arrays tho...") {
            soWhatDoYouWant = 3;
            cout << "Oh... Okay...";
            break;
        } else {
            cout << "I think, something went wrong when you've been typing your preferences. Let's try this again:" << endl;
            getline(cin, inputPreference);
        }
    }

    if (soWhatDoYouWant == 3) return 0;
    int n;
    if (soWhatDoYouWant == 1) {
        cin >> n;
        if (!smol(n)) {
            vector <int> inputData(n);
            for (int i = 0; i < n; i++) {
                cin >> inputData[i];
            }

            squarification(inputData);
            MergeSort(inputData);

            for (int i : inputData) {
                cout << i << " ";
            }
        }
    } else {
        ifstream fin;
        fin.open(R"(D:\LW2\Third\Here.txt)");
        fin >> n;
        if (n == 0) cout << "Oh no! There is no array!";
        else if (n == 1) {
            cout << "Only one? It's gonna be lonely..." << endl;
            int lonelyNumber;
            fin >> lonelyNumber;
            fin.close();
            ofstream fout;
            fout.open(R"(D:\LW2\Third\Result.txt)");
            fout << lonelyNumber * lonelyNumber;
            fout.close();
        } else {
            vector <int> inputData(n);
            for (int i = 0; i < n; i++) {
                fin >> inputData[i];
            }
            fin.close();

            squarification(inputData);
            MergeSort(inputData);

            ofstream fout;
            fout.open(R"(D:\LW2\Third\Result.txt)");
            for (int i : inputData) {
                fout << i << " ";
            }
            fout.close();
        }
    }
    return 0;
}
