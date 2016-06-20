#ifndef SIMULATION_H
#define SIMULATION_H

using namespace std;	//for now

#include <string>	//strings
#include <fstream>	//file io
#include <iostream>	//for cerr
#include <sstream>	//for stringstream	(reading in data)	XXX should be able to replace with reading characters
#include <iomanip>	//for formatting output to file
#include "K.h"		//namespace for constants
#include "coordinate.h"	//for coordinates
#include "atom.h"	//for atom class

class simulation
{
	private:
		//void (*ForEachAtom)(atom_cls*)		//this would be sooooooo nice

	public:
		//constructors------------
		simulation();
		//prototypes--------------
		void ClearData(void);			//clears all data in class
		bool ReadData(const string);	//reads datafile	XXX may want to return number of atoms read in?
		bool operator<<(const string);
		void Standardize(void);			//moves all atoms to [0,1) (usefull after reading in data) XXX would be nice to know how many were changed

		void Disassociate(void);		//unbind all
		int Associate(void);			//bonds neighbors
		bool Bond(atom_cls*, atom_cls*);//bond, Covalent Bond
		bool Bond(atom_cls*[2]);
		int Hole(coordinate,double);	//creates hole in atoms of radius
		void Passivate(atom_cls*, atom_cls*);	//passivates hole
		bool WriteData(const string);	//outputs current state to datafile
		bool operator>>(const string);
		// int UnitCell(double[3]);		//makes the scale given, and makes the atoms within it into a unit cell (returns #atoms in cell)
		bool CopyCell(unsigned int, unsigned int);		//makes a mosaic of the current cell to the given scale. (may overload as int... not too important)
		bool Scale(unsigned int[3]);
		bool Scale(unsigned int);
		bool Scale(double[3]);			//scales the model to a certain size, retaining structure, and bond lengths
		bool Scale(string,string);				//scales model to values in file.
		int Trim(void);					//trims off all atoms that are outside of bounds or non-extant
		void RemoveAtom(unsigned int, unsigned int);	//removes atom from sim.
		int PassivatedHole(double, coordinate* center=0);	//makes a passivated hole by recursion.
		int PassivatedHole(double, atom_cls*, coordinate* center=0);	//fastest hole-maker. (specify hole by atom)
		// int Remove(void);		//removes all non-extant atoms
		atom_cls* Closest(coordinate c, unsigned int E=-1);	//returns the atom closest to the coordinate of given element
		atom_cls* Center(int E=-1);	//returns the center most atom of specified element;

		double Volume(void);				//volume of lattice in m^3
		double Mass(void);					//mass of extant atoms
		unsigned int Extant(unsigned int);	//#extant atoms of element
		unsigned int Atoms(void);			//total # of extant atoms
		double Density(void);				//density of system g/cm^3
		double operator%(const unsigned int);//percent of element

		double RealDistance(coordinate, coordinate);	//the real distance to a coord
		double ModDistance(coordinate, coordinate);	//shortest distance to another atom
		double ModDistance(atom_cls*, atom_cls*);

		// void (*ForEachAtom)(unsigned int, unsigned int);	//will be usefull... buld in error catching later :)
		//variables-----------------
		string title;								//title of the file :P
		double multiplier;							//multiplier for system... unused so far...
		unsigned int elementCount[K::MAX_ELEMENTS];	//count of atoms for each element
		string element[K::MAX_ELEMENTS];			//element name
		unsigned int elementNum;					//number of elements
		string tag;									//unknown tag... (direct)
		atom_cls atom[K::MAX_ELEMENTS][K::MAX_ATOMS];	//atoms in system
		double lattice[3];			//XXX change to vector or coord later!				//lattice axis scale... unit->angstroms?
		//coordinate lattice;

};
#endif