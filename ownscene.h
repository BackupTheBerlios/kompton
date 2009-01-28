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

#ifndef KOMPTON_OWNSCENE_H
#define KOMPTON_OWNSCENE_H

#include <QGraphicsScene>
#include <QPoint>

namespace Kompton {
	class Node;
	
	class OwnScene : public QGraphicsScene {
		Q_OBJECT
		public:
			OwnScene(QObject* parent = 0);
			~OwnScene();

		protected:
			virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

		private Q_SLOTS:
			void nodeEmitClick(Kompton::Node* node);
		
		private:
			bool m_editLine;
			Node* m_startNode;
			int m_leftNodes;
			int m_rightNodes;
			QList<Node* > m_startNodes;
	};
}

#endif //KOMPTON_OWNSCENE_H
