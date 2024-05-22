#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string from_table;
    std::vector<std::string> where;
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept {
        from_table = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept {
        where.push_back(column + "='" + value + "'");
        return *this;
    }

    // WHERE с несколькими условиями
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& pair : kv) {
            where.push_back(pair.first + "='" + pair.second + "'");
        }
        return *this;
    }

    // AddColumns с несколькими полями
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        this->columns.insert(this->columns.end(), columns.begin(), columns.end());
        return *this;
    }

    std::string BuildQuery() const {
        if (from_table.empty() || columns.empty()) {
            return "";
        }

        std::ostringstream query;

        // SELECT
        query << "SELECT ";
        for (size_t i = 0; i < columns.size(); ++i) {
            if (i > 0) query << ", ";
            query << columns[i];
        }
        query << " ";

        // FROM
        query << "FROM " << from_table << " ";

        // WHERE
        if (!where.empty()) {
            query << "WHERE ";
            for (size_t i = 0; i < where.size(); ++i) {
                if (i > 0) query << " AND ";
                query << where[i];
            }
        }

        query << ";";

        return query.str();
    }
};