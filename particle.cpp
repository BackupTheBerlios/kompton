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
	: QGraphicsLineItem(QLineF(start, end), parent)
{
	setAcceptHoverEvents(true);
	QPen pen(Qt::black);
	pen.setWidth(2);
	setPen(pen);
}

Kompton::Particle::~Particle() {
}

void Kompton::Particle::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	emit particleClicked(this);
}

void Kompton::Particle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen(Qt::cyan);
	pen.setWidth(5);
	setPen(pen);
}

void Kompton::Particle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	QPen pen(Qt::black);
	pen.setWidth(2);
	setPen(pen);
}

void Kompton::Particle::newPos(const QPointF& start, const QPointF& end) {
	setLine(QLineF(start,end));
}

#include "particle.moc"
