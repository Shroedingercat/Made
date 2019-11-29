/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 * 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

class HashTable {
public:
    HashTable();
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    bool Has(const std::string& key) const;
    bool Add(const std::string& key);
    bool Remove(const std::string& key);

private:
    struct HashTableNode {
        std::string key;
        bool empty = true;
        bool visited = false;

        HashTableNode() : key(""), empty(true), visited(false){};
        HashTableNode(std::string key_, bool empty_, bool visited_) : key(std::move(key_)), empty(empty_), visited(visited_) {}
    };

    int Hash(const std::string& str) const;
    void Increase_size();
    void Rebuild();
    bool re_add;
    size_t size;
    size_t fullness;
    size_t empty_val;
    std::vector<HashTableNode> table;

};

HashTable::HashTable() {
    size = 8;
    fullness = 0;
    re_add = false;
    empty_val = 0;
    for (size_t i = 0; i < size; i++) {
        table.emplace_back();
    }
}


// метод Горнера
int HashTable::Hash(const std::string &str) const {
    int hash = 0, a = 997, m = 2048;
    for(auto letter: str) {
        hash = (hash * a + letter) % m;
    }
    return hash;
}

void  HashTable::Rebuild() {
    std::vector<HashTableNode> new_table(size), tmp = std::vector<HashTableNode>(table);
    table = new_table;
    fullness = 0;
    re_add = true;

    for (int i = 0; i < size/2; ++i) {
        if (tmp[i].visited){
            if (!tmp[i].empty) {
                Add(tmp[i].key);
                fullness++;
            }
        }
    }
    re_add = false;
}

void HashTable::Increase_size() {
    size *=2 ;
    Rebuild();
}

bool HashTable::Has(const std::string& key) const {
    assert(!key.empty());
    int h_k_i = Hash(key);
    int i = 0;
    bool flag = true;
    while (flag) {
        if(table[(h_k_i+i)%size].visited) {
            if (!table[(h_k_i+i)%size].empty) {
                if (table[(h_k_i+i)%size].key == key) {
                    return true;
                }
            }
        } else {
            return false;
        }
        h_k_i += i;
        i++;
    }
}

bool HashTable::Add(const std::string& key) {
    assert(!key.empty());

    // Не увеличиваем размерность если передобавляем элементы
    if (!re_add) {
        fullness++;
        double alpha = double(fullness) / double(size);
        if (alpha >= 3.0 / 4.0) {
            Increase_size();
        }
    }
    int h_k_i = Hash(key);
    int i = 0;
    bool flag = true;

    while (flag) {
        if (!table[(h_k_i+i)%size].visited) {
            HashTableNode node = HashTableNode(key, false, true);
            table[(h_k_i+i)%size] = node;
            flag = false;
        } else {
            if (!table[(h_k_i+i)%size].empty && table[(h_k_i+i)%size].key == key) {
                return false;
            }
            h_k_i += i;
            i++;
        }
    }
    return true;
}

bool HashTable::Remove(const std::string& key) {
    assert(!key.empty());
    int h_k_i = Hash(key);
    int i = 0;
    bool flag = true;

    while(flag) {
        if (!table[(h_k_i+i)%size].visited) {
            return false;
        } else {
            if (!table[(h_k_i+i)%size].empty && table[(h_k_i+i)%size].key == key) {
                table[(h_k_i+i)%size].empty = true;
                empty_val++;
                // перехеширование в случае большого количества удаленных элементов
                if (empty_val > size/2) {
                    Rebuild();
                }
                return true;
            }
            h_k_i += i;
            i++;
        }
    }
}

int main() {
    HashTable table;
    char command = ' ';
    std::string value;
    while (std::cin >> command >> value) {
        switch (command) {
            case '?':
                std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}