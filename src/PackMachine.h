#pragma once

class CPackMachine
{
public:
	typedef uint8_t count_t;
	static const count_t COUNT_MAX = UINT8_MAX;
	typedef char data_t;

	CPackMachine(const char outFileName[]);
	~CPackMachine();
	void SendData(data_t data);
	void Finalize();
	void SendFile(const char inFileName[]);

protected:
	data_t m_data;
	count_t m_count;
	FILE *m_outFile;

	void WriteCollectedData();
};
