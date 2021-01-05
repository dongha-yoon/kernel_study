#include <iostream>
#include <random>

using namespace std;

int main(){
    int num,max_ind;
    cin >> num >> max_ind;
    cout << num << endl;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,max_ind);

    
    for(int i=0;i<num;i++){
        cout << dis(gen) << " " << dis(gen) << endl;
    }
}