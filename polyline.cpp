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

#include "polyline.h"
#include "node.h"
#include "particle.h"

#include <QLineF>
#include <QPen>
#include <QGraphicsScene>

Kompton::PolyLine::PolyLine(const QPointF& start, const QPointF& end)
{
	Kompton::Particle* line = new Kompton::Particle(start, end, this);
	m_lineList << line;
	connect(line, SIGNAL(particleClicked(Kompton::Particle*)), this, SLOT(particleEmitClick(Kompton::Particle*)));
}

Kompton::PolyLine::~PolyLine() {
	qDeleteAll(m_nodeList);
	qDeleteAll(m_lineList);
}

void Kompton::PolyLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	Q_UNUSED(painter)
	Q_UNUSED(option)
	Q_UNUSED(widget)
}

QRectF Kompton::PolyLine::boundingRect() const {
	return QRectF();
}

void Kompton::PolyLine::particleEmitClick(Kompton::Particle* part) {
	//create a new node at correct position
	Kompton::Node* node = new Kompton::Node(this);
	QRectF rect = part->sceneBoundingRect();
	QPointF centerPos = rect.center();
	node->setPos(centerPos);
	m_nodeList << node;
	connect(node, SIGNAL(nodeClicked(QPointF)), scene(), SLOT(nodeEmitClick(QPointF)));
	node->emitClick(centerPos);
	//split the particle
	QLineF line(part->line());
	part->setLine(line.p1(), centerPos);
	Kompton::Particle* newParticle = new Kompton::Particle(centerPos, line.p2(), this);
	m_lineList.insert(m_lineList.indexOf(part) + 1, newParticle);
	connect(newParticle, SIGNAL(particleClicked(Kompton::Particle*)), this, SLOT(particleEmitClick(Kompton::Particle*)));
}

#include "polyline.moc"
