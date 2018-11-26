#include "cell.h"
#include <vector>
#include <algorithm>
cell::cell() :
	m_value(0),
	m_id(-1),
	m_row(-1),
	m_column(-1),
	m_block(-1),
	m_given(false)
{
}
cell::cell(int sukokuNo, int id, int row, int column, int block) :
	m_candidateList(std::vector<int>()),
	m_value(sukokuNo),
	m_id(id),
	m_row(row),
	m_column(column),
	m_block(block),
	m_given(false)
{
	if (m_value != 0)
	{
		m_given = true;
	}
	m_candidateList.reserve(9);
}
cell::~cell()
{
}
int cell::GetCellValue() const
{
	return this->m_value;
}
std::vector<int> cell::GetCandidateList() const
{
	return this->m_candidateList;
}
bool cell::SetCandidateList(int value)
{
	int size = m_candidateList.size();
	if (size > 1)
	{
		for (int i = 0; i < size; i++)
		{
			if (m_candidateList.at(i) == value)
			{
				m_candidateList.erase(m_candidateList.begin() + i);
				return true;
			}
		}
	}
	return false;
}
int cell::GetMID() const
{
	return m_id;
}
int cell::GetMRow() const
{
	return m_row;
}
int cell::GetMColumn() const
{
	return m_column;
}
int cell::GetMBlock() const
{
	return m_block;
}
void cell::InitialiseCandidateList()
{
	for (int i = 1; i < 10; i++)
	{
		this->m_candidateList.push_back(i);
	}
}
bool cell::GetMGiven()const
{
	return m_given;
}
void cell::SetGiven()
{
	this->m_given = true;
}
void cell::SetValue(int value)
{
	this->m_value = value;
	this->m_given = true;
}