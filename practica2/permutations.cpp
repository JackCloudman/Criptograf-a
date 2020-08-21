#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h> 
using namespace std;

  
// Function to return the next random number 
int getNum(vector<int>& v) 
{ 
  
    // Size of the vector 
    int n = v.size(); 
    srand(time(NULL)); 
    // Make sure the number is within 
    // the index range 
    int index = rand() % n; 
    // Get random number from the vector 
    int num = v[index]; 
    // Remove the number from the vector 
    swap(v[index], v[n - 1]); 
    v.pop_back(); 
  
    // Return the removed number 
    return num; 
} 
  
// Function to generate n non-repeating random numbers 
void generateRandom(std::map<int,int> &map, int n) 
{ 
    vector<int> v(n); 

    for (int i = 0; i < n; i++) 
        v[i] = i + 1; 
  
    // While vector has elements 
    // get a random number from the vector and print it 
    int i=1;
    while (v.size()) {
    	int val=getNum(v);
    	map[i] = val;
    	i++;
        //cout << getNum(v) << " "; 
    } 


} 

std::map<int, int> getInverseP(std::map<int,int> &map) 
{ 
    std::map<int, int> mapPermuted;
    std::map<int, int>::iterator itr;
    for (itr = map.begin(); itr != map.end(); ++itr) { 
        mapPermuted[itr->second]=itr->first;
    }
    return mapPermuted;
} 

/*void generatePermutations(std::map<int,int> map, int n)
{
	
	for (int i = 1; i <= n; ++i)
	{
		int aux=i;
		//if(map.find(aux) == map.end())
		//{
			map[aux] = rand()%n+1;
		//}
		
	}
	std::map<int, int>::iterator itr;
	for (itr = map.begin(); itr != map.end(); ++itr) { 
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
	
}
*/
void print_Map(std::map<int,int> &map)
{
	std::map<int, int>::iterator itr;
	for (itr = map.begin(); itr != map.end(); ++itr) { 
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
}
int main(int argc, char const *argv[])
{
	std::map<int, int> map,map2;
	generateRandom(map,10);
	print_Map(map);
    map2=getInverseP(map);
    print_Map(map2);
	return 0;
}


