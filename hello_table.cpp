#include <vector>
#include <iostream>

struct hash_t;
struct iter_t {
  hash_t *hash;
  int id;

  iter_t(hash_t *_hash, int _id = -1);
  iter_t &operator ++();
  iter_t &reach_non_empty();
  bool operator != (const iter_t & rhs) const {
    return id != rhs.id;
  }
  int operator *();
};

struct hash_t {
  std::vector<int> data;
  int a;
  int b;
  static const int c = 99990001;
  hash_t() 
    :data(10, -1)
    ,a(172384)
    ,b(272389473)
  {}

  int hash_func(int key) {
    return (a * key + b) % c;
  }

  void add(int key) {
    int hash = hash_func(key);
    for (int i = 0; i < data.size(); ++i) {
      int id = (i + hash) % data.size();
      if (data[id] == -1 or data[id] == -2) {
        data[id] = key;
        return;
      } else {
        std::cout << "Key exists [" << id <<"]" << data[id] << " ==" << key << std::endl;
      }
    }
    throw 1;
  }

  int *find(int key) {
    int hash = hash_func(key);

    for (int i = 0; i < data.size(); ++i) {
      int id = (i + hash) % data.size();
      if (data[id] == -1) {
        return NULL;
      } else if (data[id] == -2) {
        //
      } else if (data[id] == key){
        return &data[id];
      }
    }
    return NULL;
  }

  int remove(int key) {
    int *ptr = find(key);
    if( ptr != NULL && *ptr == key) {
      *ptr = -2;
      return 1;
    }
    return 0;
  }

  int size() const {
    int s = 0;
    for (int i = 0; i < data.size(); ++i) {
      if (data[i] != -1 and data[i] != -2) {
        ++s;
      }
    }
    return s;
  }

  iter_t begin() {
    iter_t it(this, 0);
    return it.reach_non_empty(); 
  }
  iter_t end() {return iter_t(this); }
};


iter_t::iter_t(hash_t *_hash, int _id) : hash(_hash), id(_id) {}
  
iter_t &iter_t::operator ++() {
  ++id;
  return reach_non_empty();
}
iter_t &iter_t::reach_non_empty() {
  for (; id < hash->data.size(); ++id) {
    if (hash->data[id] != -1 and hash->data[id] != -2) {
      return *this;
    }
  }
  id = -1;
  return *this;
}
int iter_t::operator *() {
  return hash->data[id];
}


int main() {
  int n;
  int m;
  std::cin >> n;
  std::cin >> m;
  hash_t hash;
  for(int i = 0; i < n; ++i) {
    int value = 0;
    std::cin >> value;
    if (value >=0) {
      hash.add(value);
    } else {
      hash.remove(-value);
    }
  }

  
  for(int i = 0; i < m; ++i) {
    int value;
    std::cin >> value;

    int *item = hash.find(value);
    if (item == NULL) {
      std::cout << "NONE" << std::endl;
    } else {
      std::cout << *item << std::endl;
    }
  }

  //hash.itarate(action);
  for (iter_t it = hash.begin(); it != hash.end(); ++it) {
    std::cout << "hello " << it.id << " -> " << *it << std::endl;
  }

  std::cout << "size: " << hash.size() << std::endl;
  return 0;
}
