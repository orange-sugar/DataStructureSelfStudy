#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../bitMap/Bitmap.h"

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

int primeNLT(int c, int n, char* file) {
    Bitmap B (file , n);
    while (c < n) 
        if (B.test(c)) c++;
        else return c;
    return c;
}





#endif