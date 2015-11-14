/*  BSP.H -- Type definitions for BSP code */
#include <fstream>
typedef unsigned short ushort;
typedef unsigned long ulong;
class CPoint
{
public:
	double x, y, z;
public:
	CPoint(void);
	void Read(std::ifstream& input);
	void Write(std::ofstream& output) const;
	double Magnitude(void) const;
	void Normalize(void);
	double DotProduct(const CPoint& Pnt) const;
	CPoint CrossProduct(const CPoint& Pnt) const;
	short operator==(const CPoint& Pnt) const;
	CPoint operator-(const CPoint& Pnt) const;
};
class BSPNodeList;
class BSPNode
{
private:
	ushort Index;
	BSPNode *FrontNode, *BackNode;
	short PntCnt;
	CPoint *PntList;
	CPoint Center;
	CPoint Normal;
	double D;

	ulong _SplitPoly(BSPNode *Plane, CPoint *SplitPnts);
	void _ComputeCenter(void);
	void _ComputeNormal(void);
	void _ComputeD(void);
public:
	BSPNode(void);
	~BSPNode(void);
	void ReadPoly(std::ifstream& Input);
	void ReadNode(std::ifstream& Input, const BSPNodeList& NodePool);
	void WriteNode(std::ofstream& Output, short& CurIndex);
	CPoint GetCenter(void) { return Center; }
	CPoint GetNormal(void) { return Normal; }
	bool Intersects(BSPNode *Plane);
	BSPNode *Split(BSPNode *Plane);
	BSPNode *GetFront(void) { return FrontNode; }
	BSPNode *GetBack(void) { return BackNode; }
	void SetFront(BSPNode *Node) { FrontNode = Node; }
	void SetBack(BSPNode *Node) { BackNode = Node; }
	void Traverse(const CPoint& CameraLoc);
};
class BSPNodeHeader
{
	friend class BSPListIterator;
	friend class BSPNodeList;
private:
	BSPNodeHeader *Next;
	BSPNode *Data;
	BSPNodeHeader(BSPNode *DataNode) { Data = DataNode; Next = NULL; }
	void SetNext(BSPNodeHeader *NextNode) { Next = NextNode; }
	BSPNodeHeader *GetNext(void) { return Next; }
	BSPNode *GetData(void) { return Data; }
};
class BSPNodeList
{
	friend class BSPListIterator;
private:
	BSPNodeHeader *FirstNode, *LastNode;
public:
	BSPNodeList(void);
	~BSPNodeList(void);
	void ReadPolys(std::ifstream& Input);
	bool Empty(void) { return FirstNode == NULL; }
	void Insert(BSPNode *Node);
	void Remove(BSPNode *Node);
};
class BSPListIterator
{
private:
	BSPNodeHeader *Current;
public:
	BSPListIterator(void);
	BSPNode *First(const BSPNodeList *List);
	BSPNode *Next(void);
};
class BSPTree
{
private:
	BSPNodeList Nodes;
	BSPNode *Root;
	BSPNode *_FindRoot(BSPNodeList *List);
	BSPNode *_BuildBSPTree(BSPNodeList *List);
public:
	void ReadPolyList(std::ifstream& Input);
	void ReadTree(std::ifstream& Input);
	void WriteTree(std::ofstream& Output);
	void BuildTree(void);
	void Traverse(const CPoint& CameraLoc);
};