#include "VattiEdge.h"

#include "Point2D.h"

VattiEdge::VattiEdge(Point2D start, Point2D end, VattiEdgeKind kind) : Line2D(start, end), bottomX(start.getX()), kind(kind)
{
	side = VattiEdgeSide::UNDEFINED;
	dx = (end.getX() - start.getX()) / (end.getY() - start.getY());
	bottomX = start.getX();
}

VattiEdge::VattiEdge(Point2D start, Point2D end, VattiEdgeKind kind, VattiEdgeSide side) : Line2D(start, end), kind(kind), side(side)
{
	dx = (end.getX() - start.getX()) / (end.getY() - start.getY());
	bottomX = start.getX();
}

VattiEdge::VattiEdge(const Line2D & line) : Line2D(line)
{
	dx = (end.getX() - start.getX()) / (end.getY() - start.getY());
	bottomX = start.getX();
}

VattiEdge::VattiEdge(const VattiEdge & other) : Line2D(other)
{
	this->bottomX = other.bottomX;
	this->dx = other.dx;
	this->adjPolyPtr = other.adjPolyPtr;
	this->kind = other.kind;
	this->side = other.side;
}

void VattiEdge::setBottomX(double bottomX)
{
	this->bottomX = bottomX;
}

double VattiEdge::getBottomX() const
{
	return bottomX;
}

double VattiEdge::getTopY() const
{
	return end.getY() > start.getY() ? end.getY() : start.getY();
}

double VattiEdge::getDx() const
{
	return dx;
}

VattiEdgeKind VattiEdge::getKind() const
{
	return kind;
}

void VattiEdge::setKind(VattiEdgeKind kind)
{
	this->kind = kind;
}

bool VattiEdge::contributing() const
{
	return contributing;
}

void VattiEdge::setContributing(bool contributing)
{
	this->contributing = contributing;
}

PartialPolygon * VattiEdge::getAssociatedPoly() const
{
	return adjPolyPtr;
}

void VattiEdge::setAssociatedPoly(PartialPolygon * adjPolyPtr)
{
	this->adjPolyPtr = adjPolyPtr;
}


