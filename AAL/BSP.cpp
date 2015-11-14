/* BSPNode.cpp -- Implementation of BSPNode class */
#include <assert.h>
#include "bsp.h"


using namespace std;

//-------------- Private Functions
ulong BSPNode::_SplitPoly(BSPNode *Plane, CPoint *SplitPnts)
// This is limited to convex polygons with no more than 32 sides
{
	ulong Sides = 0;
	bool LastSideParallel = false;
	if (!(Normal == Plane->Normal))
	{
		CPoint EdgeDelta;
		double numer, denom, t;
		for (ushort vertex = 0; vertex<PntCnt; vertex++)
		{
			ushort prevVertex = vertex ? vertex - 1 : PntCnt - 1;
			EdgeDelta = PntList[vertex] - PntList[prevVertex];
			denom = EdgeDelta.DotProduct(Plane->Normal);
			if (denom)
			{
				numer = PntList[prevVertex].DotProduct
					(Plane->Normal) + Plane->D;
				t = -numer / denom;
				if (!(LastSideParallel && t == 0.0))
				{
					if (t >= 0.0 && t < 0.999999)
					{
						Sides |= 1 << vertex;
						if (SplitPnts)
						{
							SplitPnts[vertex].x = PntList[prevVertex].x;
							SplitPnts[vertex].y = PntList[prevVertex].y + t * EdgeDelta.y;
							SplitPnts[vertex].z = PntList[prevVertex].z + t * EdgeDelta.z;
						}
					}
				}
			}
			LastSideParallel = (denom == 0);
		}
	}
	return Sides;
}
void BSPNode::_ComputeCenter(void)
{
	Center.x = Center.y = Center.z = 0.0;
	for (ushort i = 0; i<PntCnt; i++)
	{
		Center.x += PntList[i].x;
		Center.y += PntList[i].y;
		Center.z += PntList[i].z;
	}
	Center.x /= PntCnt;
	Center.y /= PntCnt;
	Center.z /= PntCnt;
}
void BSPNode::_ComputeNormal(void)
{
	CPoint a, b;
	assert(PntCnt >= 3);
	a = PntList[0] - PntList[1];
	b = PntList[2] - PntList[1];
	Normal = a.CrossProduct(b);
	Normal.Normalize();
}
void BSPNode::_ComputeD(void)
{
	D = -Normal.DotProduct(Center);
}
//-------------- Public Functions
BSPNode::BSPNode(void) :
	FrontNode(NULL),
	BackNode(NULL),
	Index(0),
	PntCnt(0),
	PntList(NULL)
{
}
BSPNode::~BSPNode(void)
{
	if (PntList)
		delete[] PntList;
};
void BSPNode::ReadPoly(ifstream& Input)
{
	Input >> PntCnt;
	assert(PntCnt >= 3);
	PntList = new CPoint[PntCnt];
	for (ushort i = 0; i<PntCnt; i++)
		PntList[i].Read(Input);
	_ComputeCenter();
	_ComputeNormal();
	_ComputeD();
}
void BSPNode::ReadNode(ifstream& Input, const BSPNodeList& NodePool)
{
	short FrontIndex, BackIndex;
	Input >> Index >> FrontIndex >> BackIndex;
	if (!Input)
		return;
	Input >> PntCnt;
	PntList = new CPoint[PntCnt];
	for (short i = 0; i<PntCnt; i++)
		PntList[i].Read(Input);
	_ComputeCenter();
	_ComputeNormal();
	_ComputeD();
	// Find Children
	BSPListIterator Iter;
	BSPNode *TestNode = Iter.First(&NodePool);
	FrontNode = BackNode = NULL;
	while (TestNode)
	{
		if (TestNode->Index == FrontIndex)
			FrontNode = TestNode;
		else if (TestNode->Index == BackIndex)
			BackNode = TestNode;
		if (FrontNode && BackNode)
			return;
		TestNode = Iter.Next();
	}
}
void BSPNode::WriteNode(ofstream& Output, short& CurIndex)
{
	if (FrontNode)
		FrontNode->WriteNode(Output, CurIndex);
	if (BackNode)
		BackNode->WriteNode(Output, CurIndex);
	// write index and child indices
	Index = CurIndex++;
	Output << Index << '\n';
	Output << (FrontNode ? FrontNode->Index : -1) << ' ';
	Output << (BackNode ? BackNode->Index : -1) << '\n';
	// write point list
	Output << PntCnt << '\n';
	for (short i = 0; i<PntCnt; i++)
	{
		Output << '\t';
		PntList[i].Write(Output);
	}
	Output << '\n';
}
bool BSPNode::Intersects(BSPNode *Plane)
{
	return (_SplitPoly(Plane, NULL) != 0);
}
BSPNode *BSPNode::Split(BSPNode *Plane)
{
	BSPNode *NewNode;
	CPoint *SplitPnts;
	ulong Splits;
	SplitPnts = new CPoint[PntCnt];
	Splits = _SplitPoly(Plane, SplitPnts);
	if (Splits)
	{
		CPoint *NewPoly1, *NewPoly2;
		ushort Poly1Index = 0, Poly2Index = 0;
		ushort Destination = 0;
		NewPoly1 = new CPoint[PntCnt];
		NewPoly2 = new CPoint[PntCnt];
		for (ushort i = 0; i<PntCnt; i++)
		{
			// Handle split points
			if (Splits & (1 << i))
			{
				NewPoly1[Poly1Index++] = SplitPnts[i];
				NewPoly2[Poly2Index++] = SplitPnts[i];
				Destination ^= 1;
			}
			if (Destination)
				NewPoly1[Poly1Index++] = PntList[i];
			else
				NewPoly2[Poly2Index++] = PntList[i];
		}
		// Make New node
		NewNode = new BSPNode;
		NewNode->PntCnt = Poly1Index;
		NewNode->PntList = NewPoly1;
		NewNode->Normal = Normal;
		NewNode->_ComputeCenter();
		delete[] PntList;
		PntCnt = Poly2Index;
		PntList = NewPoly2;
		_ComputeCenter();
	}
	delete SplitPnts;
	return NewNode;
}
void BSPNode::Traverse(const CPoint& CameraLoc)
{
	CPoint VecToCam = CameraLoc - Center;
	if (VecToCam.DotProduct(Normal) < 0)
	{
		if (FrontNode)
			FrontNode->Traverse(CameraLoc);
		// Process 'this'  i.e. render it to screen
		if (BackNode)
			BackNode->Traverse(CameraLoc);
	}
	else
	{
		if (BackNode)
			BackNode->Traverse(CameraLoc);
		// Process 'this'  i.e. render it to screen
		if (FrontNode)
			FrontNode->Traverse(CameraLoc);
	}
}