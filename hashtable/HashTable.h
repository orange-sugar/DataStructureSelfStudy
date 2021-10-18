#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../bitMap/Bitmap.h"
#include <cstddef>
#include <cstring>
#include <sys/types.h>

static size_t hashCode(char c) { return (size_t) c; }
static size_t hashCode(int k)  { return (size_t) k; }
static size_t hashCode(long long i) { return (size_t) ((i>>32) + (int)i); }
static size_t hashCode(char s[]) {
    unsigned int h = 0;
    for (size_t n = strlen(s), i = 0; i < n; i++) {
        h = (h << 5) | (h >> 27); 
        h += (int) s[i];
    }
    return (size_t) h;
}

template <typename K, typename V> struct Entry { //词条模板类
   K key; V value; //关键码、数值
   Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {}; //默认构造函数
   Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {}; //基于克隆的构造函数
   bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  //比较器：小于
   bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  //比较器：大于
   bool operator== ( Entry<K, V> const& e ) { return key == e.key; } //判等器：等于
   bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } //判等器：不等于
}; 

template <typename K, typename V> struct Dictionary { //词典Dictionary模板类
   virtual int size() const = 0; //当前词条总数
   virtual bool put ( K, V ) = 0; //插入词条（禁止雷同词条时可能失败）
   virtual V* get ( K k ) = 0; //读取词条
   virtual bool remove ( K k ) = 0; //删除词条
};

static int primeNLT(int c, int n, char* file) {
    Bitmap B (file , n);
    while (c < n) 
        if (B.test(c)) c++;
        else return c;
    return c;
}

template <typename K, typename V> class HashTable: public Dictionary<K, V> {
private:
    Entry<K, V>** ht;
    int M; int N;
    Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int probe4Hit(const K& k);
    int probe4Free(const K& k);
    void rehash();

public:
    HashTable(int c = 5);
    ~HashTable();
    int size() const { return N; }
    bool put(K, V);
    V* get(K k);
    bool remove(K k);
};


template<typename K, typename V> HashTable<K, V>::HashTable(int c) {
    M = primeNLT(c, 1048576, const_cast<char*>("../_input/prime-1048576-bitmap.txt"));
    N = 0; ht = new Entry<K, V>* [M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    lazyRemoval = new Bitmap(M);
}

template<typename K, typename V> HashTable<K, V>::~HashTable() {
    for (int i = 0; i < M; i++) 
        if (ht[i]) release(ht[i]);
    release(ht);
    release(lazyRemoval);
}

template<typename K, typename V>
V* HashTable<K, V>::get(K k) {
    int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : nullptr;
}

template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k) {
    int r = hashCode(k) % M;
    while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r))) 
        r = (r + 1) % M;
    return r;
}

#endif