#pragma once

#include <Printers/IPrinter.h>
#include <Tables/Table.h>

#include <Settings.h>
#include <Benchmark.h>

#include <fstream>
#include <ostream>
#include <iomanip>
#include <cfloat>
#include <cmath>

class TablePrinter : public IPrinter
{
public:
	TablePrinter(std::ostream& out,
			std::shared_ptr<Settings> settings,
			bool useDelta = false)
		: m_out(out)
		, m_precision(settings->precision)
		, m_eps(settings->eps)
		, m_useDelta(useDelta)
	{}

	void PrintStateData(const BenchmarkStateData& stateData) override
	{
		Table table;

		auto columnNames = stateData.columnNames;
		columnNames.insert(columnNames.begin(), "N");

		table.SetTitle(stateData.title);
		table.SetColumnNames(columnNames);

		const auto size = stateData.states.size();
		std::vector<double> dispValue(size, DBL_MIN);
		std::vector<std::string> dispStr(size, "");

		for (std::size_t i = 0; i < size; ++i)
		{
			auto values = stateData.states[i]->GetValues();

			std::vector<std::string> formattedValues;
			formattedValues.reserve(size + 1);
			formattedValues.push_back(ConvertToString(i + 1));

			for (std::size_t j = 0; j < values.size(); ++j)
			{
				double value = values[j];

				std::string converted = ConvertToString(value);
				if (converted != dispStr[j] || !m_useDelta)
				{
					formattedValues.push_back(converted);
					dispValue[j] = value;
					dispStr[j] = converted;
				}
				else
				{
					if (value - dispValue[j] == 0)
						converted = "-//-";
					else
						converted = ConvertToString(value - dispValue[j], true);
					formattedValues.push_back(converted);
				}
			}

			table.AddRow(formattedValues);
		}

		table.Print(m_out);
		m_out << '\n';
	}

	void PrintResultData(const std::vector<BenchmarkResultData>& resultData) override
	{
		Table table;

		table.SetTitle("Results");
		table.SetColumnNames({ "Name", "x",
				"f calls", "f' calls", "f'' calls" });

		for (const auto& result : resultData)
		{
			std::vector<std::string> values = { result.title };
			values.push_back(ConvertToString(result.result));

			values.push_back(ConvertToString(result.fCalls));
			values.push_back(ConvertToString(result.dfCalls));
			values.push_back(ConvertToString(result.ddfCalls));

			table.AddRow(values);
		}

		table.Print(m_out);
		m_out << '\n';
	}

private:
	std::ostream& m_out;
	int m_precision;
	double m_eps;
	bool m_useDelta;

	std::string ConvertToString(std::size_t value)
	{
		std::stringstream s;
		s << value;
		return s.str();
	}
	std::string ConvertToString(double value, bool isDelta = false)
	{
		std::stringstream s;

		if (isDelta)
		{
			s << "d" << std::showpos;
		}

		s << std::setprecision(m_precision) << std::scientific << value;

		return s.str();
	}
};

