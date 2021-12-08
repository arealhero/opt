#pragma once

#include <iostream>

#include <string>
#include <vector>
#include <numeric>

class Table
{
public:
	void SetTitle(const std::string& title)
	{
		m_title = title;
		/* TODO: update table width */
	}

	void SetColumnNames(const std::vector<std::string>& names)
	{
		m_columnNames.reserve(names.size());
		m_columnWidth.reserve(names.size());

		for (const auto& name : names)
		{
			m_columnNames.push_back(name);
			m_columnWidth.push_back(name.size());
		}
	}

	void AddRow(const std::vector<std::string>& values)
	{
		std::vector<std::string> row;
		row.reserve(values.size());

		for (std::size_t i = 0; i < values.size(); ++i)
		{
			const auto& value = values[i];

			row.push_back(value);
			m_columnWidth[i] =
				std::max(m_columnWidth[i], value.size());
		}

		m_rows.push_back(row);
	}

	void Print(std::ostream& out)
	{
		CalculateTableWidth();

		PrintTitle(out);
		PrintColumnHeaders(out);
		PrintRows(out);
	}

private:
	std::string m_title;
	std::vector<std::string> m_columnNames;
	std::vector<std::size_t> m_columnWidth;
	std::vector<std::vector<std::string>> m_rows;

	std::size_t m_tableWidth = 0;

	void PrintTitle(std::ostream& out) const
	{
		PrintCenter(out, m_title, m_tableWidth);
		out << "\n";
	}

	void PrintColumnHeaders(std::ostream& out) const
	{
		for (std::size_t i = 0; i < m_columnNames.size(); ++i)
		{
			const auto& name = m_columnNames[i];
			const auto& width = m_columnWidth[i];

			PrintCenter(out, name, width);
			out << " ";
		}
		out << "\n";
	}

	void PrintRows(std::ostream& out) const
	{
		for (const auto& row : m_rows)
		{
			for (std::size_t i = 0; i < row.size(); ++i)
			{
				const auto& value = row[i];
				const auto& width = m_columnWidth[i];

				if (m_columnNames[i] == "Name")
					PrintLeft(out, value, width);
				else
					PrintRight(out, value, width);
				out << " ";
			}
			out << "\n";
		}
	}

	void CalculateTableWidth()
	{
		m_tableWidth =
			std::accumulate(m_columnWidth.begin(), 
				m_columnWidth.end(), 0)
			+ m_columnWidth.size() - 1;
	}

	static void PrintCenter(std::ostream& out,
			const std::string& str, std::size_t width)
	{
		const auto size = str.size();
		const std::size_t padding = (width - size) / 2;

		PrintSpaces(out, padding);
		out << str;
		PrintSpaces(out, width - size - padding);
	}
	static void PrintLeft(std::ostream& out,
			const std::string& str, std::size_t width)
	{
		const auto size = str.size();
		const std::size_t padding = width - size;

		out << str;
		PrintSpaces(out, padding);
	}
	static void PrintRight(std::ostream& out,
			const std::string& str, std::size_t width)
	{
		const auto size = str.size();
		const std::size_t padding = width - size;

		PrintSpaces(out, padding);
		out << str;
	}

	static void PrintSpaces(std::ostream& out, std::size_t count)
	{
		for (std::size_t i = 0; i < count; ++i)
			out << " ";
		/* out << std::string(" ", count); */
	}
};

