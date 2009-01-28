/***************************************************************************
 *   Copyright (C) 2009 Felix Lemke <lemke.felix@ages-skripte.org>          
 *                                                                          
 *   This program is free software; you can redistribute it and/or          
 *   modify it under the terms of the GNU General Public                    
 *   License as published by the Free Software Foundation; either           
 *   version 2 of the License, or (at your option) any later version.       
 *                                                                          
 *   This program is distributed in the hope that it will be useful,        
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          
 *   GNU General Public License for more details.                           
 *                                                                          
 *   You should have received a copy of the GNU General Public License      
 *   along with this program; if not, write to the Free Software            
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
***************************************************************************/  

#include "node.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

Kompton::Node::Node(QGraphicsItem* parent)
	: QGraphicsEllipseItem(-10, -10, 20, 20, parent)
	, m_isStartNode(false)
{
	setAcceptHoverEvents(true);
	QPen pen = QPen();
	pen.setWidth(2);
	pen.setColor(Qt::black);
	setPen(pen);
}

Kompton::Node::~Node() {
}

void Kompton::Node::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	event->accept();
	emit nodeClicked(this);
}

void Kompton::Node::emitClick(Kompton::Node* node) {
	emit nodeClicked(node);
}

void Kompton::Node::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	QPen pen;
	pen.setWidth(5);
	pen.setColor(Qt::cyan);
	setPen(pen);
	pen.setColor(Qt::red);
	foreach (Kompton::Node* neighbour, m_neighbours) neighbour->setPen(pen);
}

void Kompton::Node::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::black);
	setPen(pen);
	foreach (Kompton::Node* neighbour, m_neighbours) neighbour->setPen(pen);
}

#include <kdebug.h>
void Kompton::Node::findPosition() {
	if (m_isStartNode == false) {
		int nodeOverThis = 0;
		int nodeLeftOfThis= 0;
		int nodeUnderThis = 0;
		int nodeRightOfThis = 0;
		QPointF ownPos = pos();
		foreach (Kompton::Node* neighbour, m_neighbours) {
			QPointF neighbourPos = neighbour->pos();
			if (neighbourPos.x() < ownPos.x()) ++nodeLeftOfThis; else ++nodeRightOfThis;
			if (neighbourPos.y() > ownPos.y()) ++nodeUnderThis; else ++nodeOverThis;
		}
		kDebug() << "Links: " << nodeLeftOfThis << " Ueber: " << nodeOverThis << " Rechts: " << nodeRightOfThis << " Unter: " << nodeUnderThis;
	}
}

#include "node.moc"