#include <iostream>
#include <random>

using namespace std;

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,2147483647);

    int num;
    cin >> num;
    cout << num << endl;
    for(int i=0;i<num;i++){
        cout << dis(gen) << " " << dis(gen) << endl;
    }
}