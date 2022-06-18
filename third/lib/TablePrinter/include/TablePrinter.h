#pragma once

#include <ostream>

#include <string>
#include <vector>

class TablePrinter
{
public:
	void SetTitle(const std::string& title);
	void SetColumnNames(const std::vector<std::string>& names);

	void AddRow(const std::vector<std::string>& values);

	void Print(std::ostream& out);

private:
	std::string m_title;
	std::vector<std::string> m_columnNames;
	std::vector<std::size_t> m_columnWidth;
	std::vector<std::vector<std::string>> m_rows;

	std::size_t m_tableWidth = 0;

	void PrintTitle(std::ostream& out);
	void PrintColumnHeaders(std::ostream& out);
	void PrintRows(std::ostream& out);

	void CalculateTableWidth();

	static void PrintCenter(std::ostream& out,
			const std::string& str, std::size_t width);
	static void PrintLeft(std::ostream& out,
			const std::string& str, std::size_t width);
	static void PrintRight(std::ostream& out,
			const std::string& str, std::size_t width);
	static void PrintSpaces(std::ostream& out, std::size_t count);
};

