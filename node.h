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

#ifndef KOMPTON_NODE_H
#define KOMPTON_NODE_H

#include <QGraphicsEllipseItem>
#include <QObject>

namespace Kompton {
	class Node : public QObject, public QGraphicsEllipseItem {
		Q_OBJECT
		public:
			Node(QGraphicsItem* parent = 0);
			virtual ~Node();

			virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
			virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
			virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
			void emitClick(Kompton::Node* node);

			inline void addNeighbour(Node* neighbour) { m_neighbours << neighbour; }
			inline void removeNeighbour(Node* neighbour) {m_neighbours.removeAll(neighbour); }
			
		Q_SIGNALS:
			void nodeClicked(Kompton::Node* node);

		private:
			QList<Node* > m_neighbours;
	};
}

#endif //KOMPTON_NODE_H
