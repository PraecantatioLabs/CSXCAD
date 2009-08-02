#pragma once
/*
 * Author:	Thorsten Liebig
 * Date:	03-12-2008
 * Lib:		CSXCAD
 * Version:	0.1a
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ParameterObjects.h"
#include "CSXCAD_Global.h"

class TiXmlNode;


//! CSRectGrid is managing a recilinear graded mesh.
class CSXCAD_EXPORT CSRectGrid
{
public:
	//! Create an empty grid.
	CSRectGrid(void);
	//! Deconstruct the grid.
	~CSRectGrid(void);

	//! Add a disc-line in the given direction.
	void AddDiscLine(int direct, double val);
	void AddDiscLines(int direct, int numLines, double* vals);
	string AddDiscLines(int direct, int numLines, double* vals, string DistFunction);

	//! Remove the disc-line at certain index and direction.
	bool RemoveDiscLine(int direct, int index);
	//! Remove the disc-line at certain value and direction.
	bool RemoveDiscLine(int direct, double val);

	//! Remove all lines and reset to an empty grid.
	void clear();
	//! Clear all lines in a given direction.
	void ClearLines(int direct);

	//! Set the drawing unit. e.g. 1e-3 for mm as drawing unit.
	void SetDeltaUnit(double val) {dDeltaUnit=val;};
	//! Get the current drawing unit.
	double GetDeltaUnit() {return dDeltaUnit;};

	//! Get an array of discretization lines in a certain direction.
	/*!
	\param direct The direction of interest.
	\param array The array in which the lines will be stored. Can be NULL. Caller has to delete the array.
	\param qty Methode will return the number of lines in this direction.
	\param sorted Define here whether the lines shall be in increasing order (default) or as currently stored (unknown order).
	 */
	double* GetLines(int direct, double *array, unsigned int &qty, bool sorted=true);
	//! Get quantity of lines in certain direction.
	size_t GetQtyLines(int direct) {if ((direct>=0) && (direct<3)) return Lines[direct].size(); else return 0;};
	//! Get a disc-line in a certain direction an at given index.
	double GetLine(int direct, size_t Index);
	//! Get disc-lines as a comma-seperated string for given direction
	string GetLinesAsString(int direct);

	//! Write the grid to a given XML-node.
	bool Write2XML(TiXmlNode &root, bool sorted=false);
	//! Read the grid from a given XML-node.
	bool ReadFromXML(TiXmlNode &root);

	//! Get the dimension of current grid. \return 0,1,2 or 3. Returns -1 if one or more directions have no disc-line at all.
	int GetDimension();

	//! Increase the resolution in the specified direction by the given factor.
	void IncreaseResolution(int nu, int factor);

	//! Sort the lines in a given direction.
	void Sort(int direct);

	//! Get the bounding box of the area defined by the disc-lines.
	double* GetSimArea();

protected:
	vector<double> Lines[3];
	double dDeltaUnit;
	double SimBox[6];
};