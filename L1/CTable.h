#include <string>

#ifndef L1_CTABLE_H
#define L1_CTABLE_H


class CTable {
    private:
    std::string table_name;
    int table_size;
    int *table;

    const std::string DEFAULT_NAME = "Table";
    const int DEFAULT_SIZE = 20;

    public:
    CTable();
    CTable(const std::string& name, int size);
    CTable(CTable const &table);
    ~CTable();
    void setName(const std::string& name);
    std::string getName() const;
    bool setSize(int size);
    int getSize() const;
    CTable *clone() const;

    void fillTable(int *list, int size);
    void printTable();
    void insertHere(CTable &table, int position);
};


#endif //L1_CTABLE_H