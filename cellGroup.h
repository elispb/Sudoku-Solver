#pragma once
#include "cell.h"
class cellGroup {
public: 
	cellGroup(void);
	~cellGroup(void);
	void SetCell(int index, cell *cell);
	// Other Methods
	cell& GetCell(int index) const;
private: 
	cell* m_cells[9];
};