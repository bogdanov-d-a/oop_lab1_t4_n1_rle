#pragma once

class CUnpackMachine
{
public:
	typedef uint8_t count_t;
	typedef char data_t;

	CUnpackMachine(const char outFileName[]);
	~CUnpackMachine();
	void SendData(count_t count, data_t data);
	void Finalize();
	void SendFile(const char inFileName[]);

protected:
	static const char *FILE_OPEN_ERROR_MSG;
	static const char *FILE_DAMAGED_MSG;

	FILE *m_outFile;
};
