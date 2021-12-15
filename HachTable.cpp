#include <iostream>
#include<list>
#include<algorithm>
using namespace std;

class HashTable
{
  private:
    list <int> * map;
    int size;
    int hash (int data){
      return data%size;
    }
  public:
    HashTable(int size) {
      this->size = size;
      map = new list <int> [this->size];
    }
    ~HashTable (){
      delete [] map;
    }
    void insert (int data) 
    {
      int bucket = hash (data);
      map[bucket].push_front (data);
    }
    bool search (int data){
      int bucket = hash(data);
      auto it = find(map[bucket].begin(), map[bucket].end(), data);
      if (it == map[bucket].end())
        return false;
      else 
        return true;
    }
    void print (){
      for(int i=0; i<size; i++){
        cout << i << ": ";
        for(auto it = map[i].begin(); it != map[i].end(); it++)
        {
          cout << *it << " ";
        }
        cout << endl;
      }
    }
    void remove(int data){
      int bucket = hash(data);
      auto it = find(map[bucket].begin(), map[bucket].end(), data);
      if (it == map[bucket].end())
        return;
      map[bucket].erase(it);
    }
};

int main(int argc, const char * argv[])
{
  HashTable ht(10);
  ht.insert(10);
  ht.insert(33);
  ht.insert(34);
  ht.insert(53);
  cout << ht.search(33) << endl;
  cout << ht.search(11) << endl;
  ht.print();
  ht.remove(33);
  ht.print();
  return 0;
}
