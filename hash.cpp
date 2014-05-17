#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template <class key_t>
struct hash_func_t {
  hash_func_t(size_t a = 172612847, size_t b = 63783492, size_t c = (size_t(1)<<31) - 1)
    :_a(a)
    ,_b(b)
    ,_c(b) {}

  size_t operator () (key_t &key);

  size_t _a, _b, _c;
};

template <class key_t, class data_t, class hfunc_t = hash_func_t<key_t> >
class hash_t {
public:
  struct item_t {
  	item_t() : item_type(ITEM_NONE) {}

    enum item_type_t {ITEM_NONE = 0,ITEM_BUSY, ITEM_DELETED} item_type;
    data_t data;
    key_t key;
  };

  hash_t(size_t n = 0, const hfunc_t &hfunc = hfunc_t())
    :_data(n)
    ,_size(0)
    ,_hfunc(hfunc)
    {}

  void add(const item_t &item);
  bool add_no_rebuild(const item_t &item); // return false on fail
  void rebuild();
  item_t* find(const key_t &key);
  const item_t* find(const key_t &key) const;
  
  bool remove(const key_t &key) {
    item_t *item_ptr = find(key);
    if (item_ptr != NULL) {
      item_ptr->item_type = item_t::ITEM_DELETED;
      return true;
    }
    return false;
  }

  bool empty() {return _size == 0;};
  size_t size() { return _size; }
  size_t capacity() {return _data.size(); }

private:
  std::vector<item_t> _data;
  size_t _size;
  const hfunc_t &_hfunc;
};

int main() {
  
  hash_t<int, int> h(10);

  return 0;
}