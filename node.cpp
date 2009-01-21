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

#include <QPainter>

#include "node.h"

Kompton::Node::Node(QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, m_ellipse(new QGraphicsEllipseItem(-10, -10, 20, 20, this))
{
	setAcceptHoverEvents(true);
	QPen pen = QPen();
	pen.setWidth(2);
	pen.setColor(Qt::black);
	m_ellipse->setPen(pen);
}

Kompton::Node::~Node(){
	delete m_ellipse;
}

void Kompton::Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}

QRectF Kompton::Node::boundingRect() const {
	return QRectF(m_ellipse->boundingRect());
}

// #include <QGraphicsSceneMouseEvent>
// #include <kdebug.h>
void Kompton::Node::mousePressEvent(QGraphicsSceneMouseEvent* event) {
// 	kDebug() << QString("Mouse pressed ") << event->button();
	emit nodeClicked(QPointF(x(),y()));
}

void Kompton::Node::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen = QPen();
	pen.setWidth(5);
	pen.setColor(Qt::cyan);
	m_ellipse->setPen(pen);
}

void Kompton::Node::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen = QPen();
	pen.setWidth(2);
	pen.setColor(Qt::black);
	m_ellipse->setPen(pen);
}

#include "node.moc"