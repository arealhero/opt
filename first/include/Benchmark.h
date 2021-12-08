#pragma once

#include <Benchmark/BenchmarkStateData.h>
#include <Benchmark/BenchmarkResultData.h>

#include <Settings.h>

#include <Methods/IMethod.h>
#include <States/IMethodState.h>

#include <Printers/IPrinter.h>

#include <vector>
#include <string>
#include <memory>

class Benchmark
{
public:
	explicit Benchmark(std::shared_ptr<Settings> settings)
		: m_settings(settings)
	{}

	template<typename MethodType>
	void Run()
	{
		m_settings->ClearCalls();

		const std::string methodTitle = MethodType::GetTitle();

		BenchmarkStateData stateData;
		BenchmarkResultData resultData;

		stateData.title = methodTitle;
		stateData.columnNames = MethodType::GetColumnNames();

		resultData.title = methodTitle;

		auto method = std::make_shared<MethodType>(m_settings);
		method->Init();

		do
		{
			stateData.states.push_back(method->GetState());
		}
		while (method->Iterate());

		resultData.result = method->GetResult();
		resultData.fCalls = m_settings->f.GetCalls();
		resultData.dfCalls = m_settings->df.GetCalls();
		resultData.ddfCalls = m_settings->ddf.GetCalls();

		m_stateData.push_back(stateData);
		m_resultData.push_back(resultData);
	}

	void PrintResults(std::shared_ptr<IPrinter> printer)
	{
		for (auto& stateData : m_stateData)
		{
			printer->PrintStateData(stateData);
		}

		printer->PrintResultData(m_resultData);
	}

	void Clear()
	{
		m_stateData.clear();
		m_resultData.clear();
	}

private:
	std::vector<BenchmarkStateData> m_stateData;
	std::vector<BenchmarkResultData> m_resultData;
	std::shared_ptr<Settings> m_settings;
};

