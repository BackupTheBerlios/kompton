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
	//FIXME: proper deletion of polylines, nodes, and such
// 	qDeleteAll(m_nodeList);
// 	qDeleteAll(m_lineList);
}

void Kompton::PolyLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	Q_UNUSED(painter)
	Q_UNUSED(option)
	Q_UNUSED(widget)
}

QRectF Kompton::PolyLine::boundingRect() const {
	return QRectF();
}

void Kompton::PolyLine::particleEmitClick(Kompton::Particle* particle) {
	//create a new node at correct position
	Kompton::Node* node = new Kompton::Node(this);
	QRectF rect = particle->sceneBoundingRect();
	QPointF centerPos = rect.center();
	node->setPos(centerPos);
	//right position of node in list
	int leftNodeIndex = m_lineList.indexOf(particle);
	Kompton::Node* leftNode = m_nodeList.value(leftNodeIndex);
	Kompton::Node* rightNode = m_nodeList.value(leftNodeIndex + 1);
	m_nodeList.insert(leftNodeIndex + 1, node);
	//change neighbours
	leftNode->removeNeighbour(rightNode);
	rightNode->removeNeighbour(leftNode);
	leftNode->addNeighbour(node);
	rightNode->addNeighbour(node);
	node->addNeighbour(leftNode);
	node->addNeighbour(rightNode);
	connect(node, SIGNAL(nodeClicked(Kompton::Node*)), scene(), SLOT(nodeEmitClick(Kompton::Node*)));
	node->emitClick(node);
	//split the particle
	QLineF line(particle->line());
	particle->setLine(line.p1(), centerPos);
	Kompton::Particle* newParticle = new Kompton::Particle(centerPos, line.p2(), this);
	newParticle->setStyle(particle->style());
	m_lineList.insert(m_lineList.indexOf(particle) + 1, newParticle);
	connect(newParticle, SIGNAL(particleClicked(Kompton::Particle*)), this, SLOT(particleEmitClick(Kompton::Particle*)));
}

void Kompton::PolyLine::addStartEndNodes(Node* startNode, Node* endNode) {
	m_nodeList << startNode;
	m_nodeList << endNode;
}

#include "polyline.moc"
