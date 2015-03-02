#include "stdafx.h"
#include "PackMachine.h"

CPackMachine::CPackMachine(const char outFileName[])
{
	m_data = '\0';
	m_count = 0;

	if (fopen_s(&m_outFile, outFileName, "wb") != 0)
	{
		throw std::runtime_error("Output file open error");
	}
}

CPackMachine::~CPackMachine()
{
	if (m_outFile != nullptr)
	{
		Finalize();
	}
}

void CPackMachine::SendData(data_t data)
{
	if (m_count == COUNT_MAX || (m_count != 0 && m_data != data))
	{
		WriteCollectedData();
	}

	m_data = data;
	++m_count;
}

void CPackMachine::Finalize()
{
	assert(m_outFile != nullptr);

	WriteCollectedData();
	fclose(m_outFile);

	m_outFile = nullptr;
}

void CPackMachine::SendFile(const char inFileName[])
{
	FILE *inFile;

	if (fopen_s(&inFile, inFileName, "rb") == 0)
	{
		int tmpChar;
		while ((tmpChar = fgetc(inFile)) != EOF)
		{
			SendData(tmpChar);
		}

		fclose(inFile);
	}
	else
	{
		throw std::runtime_error("Input file open error");
	}
}

void CPackMachine::WriteCollectedData()
{
	assert(m_outFile != nullptr);

	putc(m_count, m_outFile);
	putc(m_data, m_outFile);

	m_count = 0;
}
