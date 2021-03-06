#include "atom.h"
//----------------------CONSTRUCTORS--------------------------------------
atom_cls::atom_cls(const atom_cls& atom)	//should not copy bonds
{
	bond.clear();			//remove bonds
	coord = atom.coord;		//copy coordinates,
	exists = atom.exists;	//extant,
	atomicN = atom.atomicN;	//atomicN,
	freedom.reserve(atom.freedom.size());	//reserve space
	freedom = atom.freedom;	//freedoms
}
atom_cls::atom_cls(int AN, coordinate C, vector<bool> & F)
{
	atomicN = AN;
	coord = C;
	if(F.size() == 3) freedom = F;
	else 
	{
		freedom.reserve(3);
		fill(freedom.begin(), freedom.end(), 1);
	}
	exists = 1;
}
atom_cls::atom_cls(int AN, coordinate C)
{
	atomicN = AN;
	coord = C;
	freedom.resize(3,1);
	exists = 1;
}
atom_cls::~atom_cls()
{
	//nothing to delete yet.
}
//---------------------MEMBER FUNCTIONS-----------------------------------------
atom_cls& atom_cls::operator=(const atom_cls& atom)
{
	bond.clear();			//bonds
	coord = atom.coord;		//coords
	exists = atom.exists;	//extant
	atomicN = atom.atomicN;	//atomicNumber
	freedom = atom.freedom;	//freedoms
	return (*this);
}
void atom_cls::BreakBond(atom_cls* atomP)
{
	vector<atom_cls*>::iterator it = find_if(bond.begin(), bond.end(), [atomP](atom_cls* P){return atomP==P;});
	if(it == bond.end()) return;	//no bonds to atomP
	bond.erase(it);					//remove bond
	return;
}
bool atom_cls::IsBound(atom_cls* atomP)
{
	if(bond.end() == find_if(bond.begin(), bond.end(), [atomP](atom_cls* P){return atomP==P;}))
		return 0;	//not found;
	return 1;	//found it!
}

