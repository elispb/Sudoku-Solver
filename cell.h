#pragma once
#include <vector>

class cell {
public:
	cell(void);
	~cell(void);
	cell(int sudokuNo, int id, int row, int column, int block);
	// Methods	
	void cell::InitialiseCandidateList();
	bool GetMGiven()const;
	int GetCellValue() const;
	std::vector<int> GetCandidateList() const;
	int GetMID()const;
	int GetMRow()const;
	int GetMColumn()const;
	int GetMBlock()const;
	void SetValue(int value);
	void SetGiven();
	bool SetCandidateList(int value);
private: 
	std::vector<int> m_candidateList;
	int m_value;	
	int m_id;
	int m_row;
	int m_column;
	int m_block;
	bool m_given;
};
