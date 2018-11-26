#include "cellGroup.h"



cellGroup::cellGroup()
{
	//for (int i = 0; i < 9; i++)
	//{
		m_cells[9] = &cell();
	//}
}


cellGroup::~cellGroup()
{
}

void cellGroup::SetCell(int index, cell *cell)
{
	m_cells[index] = cell;
}

cell& cellGroup::GetCell(int index) const
{
	return *m_cells[index];
}

