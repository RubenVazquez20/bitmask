#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <map>
// #include<bits/stdc++.h>

using namespace std;
// string strings[max]; // define max string  

int dp(int hat, int &mask, int n, int ans, map<int, vector<int>> h2p, map<pair<int, int>, int> memo) {
  if (memo.find({hat, mask}) != memo.end())
    return memo[{hat, mask}];

  // cout << "bitmask: " << (1 << n) - 1 << endl;
  // cout << "bitset: " << mask << endl;
  if (mask == (1 << n) - 1) {
    
    // cout << "All 1s" << endl;
    return 1;
  }
  
  if (hat > 100) {
    // cout << "Top down" << endl;
    return 0;
  }

  ans = dp(hat + 1, mask, n, ans, h2p, memo);
  
  if (h2p.find(hat) != h2p.end()) {
    // cout << "Enter" << endl;
    vector<int> peoples = h2p[hat];

    for (int p: peoples) {
      if ((mask & (1 << p)) == 0) {
        mask |= (1 << p);
        ans += dp(hat + 1, mask, n, ans, h2p, memo);
        // cout << "Backtrackng" << endl;
        mask ^= (1 << p);
      }
    }
  }


  // cout << hat << " - " << mask << endl;
  memo[{hat, mask}] = ans;

  return ans;
}

int numberOfWays(vector<vector<int>> hats) {
//Como llave tiene un entero y como valor un vector de enteros
  map<int, vector<int>> h2p;
  int n = hats.size();
  int p = 0;

  // Relate hats to persons
  for (vector<int> hat_list: hats) {
    for (int hat: hat_list) {
      h2p[hat].push_back(p);
    }
    p++;
  }

  map<pair<int, int>, int> memo;
  int ans = 0;
  int mask = 0;

  return dp(0, mask, n, ans, h2p, memo);
}

int main() {
  vector<vector<int>> colecciones;
  int n;
  cin >> n;
  // cout << "n: " << n << endl;
//----------- READ INPUT --------------------------
  cin.clear();
  cin.ignore();

  for(size_t i = 0; i < n; i++){
    vector <int> coleccion;
    string str;
    getline(cin, str);  // to get rid of newline character
  
    char *ptr; // declare a ptr pointer
    size_t len = str.length();
    char pos[len];
    strcpy(pos, str.c_str());  
    ptr = strtok(pos, " "); // use strtok() function to separate string using comma (,) delimiter.  
  
    while (ptr != NULL){  
      int tmp = atoi(ptr);
      coleccion.push_back(tmp);
      ptr = strtok(NULL, " ");  
    }
  
    // for (auto x: coleccion){
    //   cout<< x << " ";
    // }  

    colecciones.push_back(coleccion);
    coleccion.clear();
  }

  for(auto x: colecciones){
    for(auto y: x){
      cout<< y << " ";
    }
    cout<<endl;
  }

  cout << numberOfWays(colecciones) << endl;

  return 0;
}