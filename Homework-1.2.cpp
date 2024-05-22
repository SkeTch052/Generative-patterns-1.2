#include <iostream>
#include <string>
#include <cassert>
#include "sql_query_builder.h"

int main() {
    setlocale(LC_ALL, "Russian");

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone" })
                 .AddFrom("students")
                 .AddWhere({ {"id", "42"}, {"name", "John"} });

    std::string query = query_builder.BuildQuery();

    // Сравните с ожидаемым результатом
    std::string expected_query = "SELECT name, phone FROM students WHERE id='42' AND name='John';";
    assert(query == expected_query && "Ошибка: Запрос не соответствует ожидаемому результату.");
    std::cout << "Запрос успешно сформирован: " << query << std::endl;

    return 0;
}