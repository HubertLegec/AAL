#ifndef VATTI_EDGE
#define VATTI_EDGE

#include "Line2D.h"
#include "PartialPolygon.h"

enum VattiEdgeKind {
	CLIP = 0,
	SUBJECT = 1
};

enum VattiEdgeSide {
	LEFT = 0,
	RIGHT = 1,
	UNDEFINED = 2
};

class VattiEdge : public Line2D
{
private:
	//initially the x-coodinate of the bottom vertex, 
	//but once the edge is on the AEL, then it is the x - intercept of the edge with the line at the bottom of the current scanbeam
	double bottomX;
	//the reciprocal of the slope of the edge
	double dx;
	//does edge belong to clip or subject polygon?
	VattiEdgeKind kind;
	//is it a left or right bound edge?
	VattiEdgeSide side;
	//does edge contribute to output polygons?
	bool contributing = false;
	//pointer to partial polygon associated to the edge
	PartialPolygon* adjPolyPtr = nullptr;

public:
	VattiEdge(Point2D start, Point2D end, VattiEdgeKind kind);
	VattiEdge(Point2D start, Point2D end, VattiEdgeKind kind, VattiEdgeSide side = VattiEdgeSide::UNDEFINED);
	VattiEdge(const Line2D& line);
	VattiEdge(const VattiEdge& other);

	void setBottomX(double bottomX);
	double getBottomX() const;
	//y-coordinate of top vertex
	double getTopY() const;
	double getDx() const;
	VattiEdgeKind getKind() const;
	void setKind(VattiEdgeKind kind);
	bool contributing() const;
	void setContributing(bool contributing);
	PartialPolygon* getAssociatedPoly() const;
	void setAssociatedPoly(PartialPolygon* adjPolyPtr);
};

#endif

