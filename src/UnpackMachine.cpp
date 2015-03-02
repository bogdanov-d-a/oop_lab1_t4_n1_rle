#include "stdafx.h"
#include "UnpackMachine.h"

CUnpackMachine::CUnpackMachine(const char outFileName[])
{
	if (fopen_s(&m_outFile, outFileName, "wb") != 0)
	{
		throw std::runtime_error("Output file open error");
	}
}

CUnpackMachine::~CUnpackMachine()
{
	if (m_outFile != nullptr)
	{
		Finalize();
	}
}

void CUnpackMachine::SendData(count_t count, data_t data)
{
	assert(m_outFile != nullptr);
	assert(count != 0);

	for (count_t i = 0; i < count; ++i)
	{
		putc(data, m_outFile);
	}
}

void CUnpackMachine::Finalize()
{
	assert(m_outFile != nullptr);
	fclose(m_outFile);
	m_outFile = nullptr;
}

void CUnpackMachine::SendFile(const char inFileName[])
{
	FILE *inFile;

	if (fopen_s(&inFile, inFileName, "rb") != 0)
	{
		throw std::runtime_error(FILE_OPEN_ERROR_MSG);
	}


	if (fseek(inFile, 0, SEEK_END) != 0)
	{
		fclose(inFile);
		throw std::runtime_error(FILE_OPEN_ERROR_MSG);
	}

	long int ftellResult = ftell(inFile);

	if (fseek(inFile, 0, SEEK_SET) != 0)
	{
		fclose(inFile);
		throw std::runtime_error(FILE_OPEN_ERROR_MSG);
	}


	if (ftellResult == -1L)
	{
		fclose(inFile);
		throw std::runtime_error(FILE_OPEN_ERROR_MSG);
	}

	if (ftellResult % 2 != 0)
	{
		fclose(inFile);
		throw std::runtime_error(FILE_DAMAGED_MSG);
	}


	int countChar, dataChar;
	do
	{
		countChar = fgetc(inFile);
		dataChar = fgetc(inFile);
		assert((countChar == EOF) == (dataChar == EOF));

		if (countChar != EOF)
		{
			if (countChar == 0)
			{
				fclose(inFile);
				throw std::runtime_error(FILE_DAMAGED_MSG);
			}

			SendData(countChar, dataChar);
		}
	}
	while (countChar != EOF);

	fclose(inFile);
}

const char *CUnpackMachine::FILE_OPEN_ERROR_MSG = "Input file open error";
const char *CUnpackMachine::FILE_DAMAGED_MSG = "Input file is damaged";
