#include "sequential_search.h"

int main() {
    SequentialSearchSymbolTable<std::string, int> table;
    table.put("apple", 1);
    table.put("banana", 2);
    table.put("cherry", 3);

    table.print();

    if (table.contains("banana")) {
        std::cout << "banana: " << *table.get("banana") << std::endl;
    }

    table.remove("banana");
    table.print();
    return 0;
}
