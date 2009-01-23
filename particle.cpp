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

#include <QGraphicsLineItem>
#include <QLineF>
#include <QPen>

#include "particle.h"

Kompton::Particle::Particle(const QPointF& start, const QPointF& end, QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, m_line(new QGraphicsLineItem(QLineF(start, end),this))
{
	setAcceptHoverEvents(true);
	QPen pen = QPen();
	pen.setWidth(2);
	pen.setColor(Qt::black);
	m_line->setPen(pen);
}

Kompton::Particle::~Particle() {
	delete m_line;
}

void Kompton::Particle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}

QRectF Kompton::Particle::boundingRect() const {
	return QRectF(m_line->boundingRect());
}

void Kompton::Particle::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	emit particleClicked(this);
}

void Kompton::Particle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen = QPen();
	pen.setWidth(5);
	pen.setColor(Qt::cyan);
	m_line->setPen(pen);
}

void Kompton::Particle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen = QPen();
	pen.setWidth(2);
	pen.setColor(Qt::black);
	m_line->setPen(pen);
}

void Kompton::Particle::setPen(const QPen& pen) {
	m_line->setPen(pen);
}

void Kompton::Particle::newPos(const QPointF& start, const QPointF& end) {
	m_line->setLine(QLineF(start,end));
}

QLineF Kompton::Particle::getLine() const {
	return m_line->line();
}

#include "particle.moc"
