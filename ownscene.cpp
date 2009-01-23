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

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

#include "ownscene.h"
#include "node.h"
#include "polyline.h"

Kompton::OwnScene::OwnScene(QObject* parent)
	: QGraphicsScene(parent)
	, m_editLine(bool(false))
	, m_startPos(QPoint(0,0))
	, m_leftNodes(3)
	, m_rightNodes(4)
{
	setSceneRect(0, 0, 500, 500);
	addRect(sceneRect());
	//left Nodes
	qreal xPos = sceneRect().left();
	qreal yPos = sceneRect().top() + sceneRect().height() / (2*m_leftNodes);
	for (int i = 0; i < m_leftNodes; ++i) {
		Kompton::Node* node = new Kompton::Node;
		node->setPos(xPos,yPos);
		yPos += sceneRect().height() / m_leftNodes;
		addItem(node);
		connect(node, SIGNAL(nodeClicked(QPointF)), this, SLOT(nodeEmitClick(QPointF)));
	}
	//right nodes
	xPos = sceneRect().right();
	yPos = sceneRect().top() + sceneRect().height() / (2*m_rightNodes);
	for (int i = 0; i < m_rightNodes; ++i) {
		Kompton::Node* node = new Kompton::Node;
		node->setPos(xPos,yPos);
		yPos += sceneRect().height() / m_rightNodes;
		addItem(node);
		connect(node, SIGNAL(nodeClicked(QPointF)), this, SLOT(nodeEmitClick(QPointF)));
	}
}

Kompton::OwnScene::~OwnScene() {
}

void Kompton::OwnScene::nodeEmitClick(const QPointF pos) {
	if (m_editLine == true) {
		m_editLine = false;
		Kompton::PolyLine* line = new Kompton::PolyLine(m_startPos, pos);
		addItem(line);
	}
	else {
		m_editLine = true;
		m_startPos = pos;
	}
}

#include "ownscene.moc"
