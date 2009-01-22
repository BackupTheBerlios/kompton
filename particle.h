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

#ifndef KOMPTON_PARTICLE_H
#define KOMPTON_PARTICLE_H

#include <QGraphicsItem>
#include <QObject>
#include <QRectF>

class QGraphicsLineItem;

namespace Kompton {
	class Particle : public QObject, public QGraphicsItem {
		Q_OBJECT
		public:
			Particle(const QPointF& start, const QPointF& end, QGraphicsItem* parent = 0);
			~Particle();

			virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
			virtual QRectF boundingRect() const;
			virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
			virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
			virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

			void setPen(const QPen& pen);

		Q_SIGNALS:
			void particleClicked(Particle* particle);

		private:
			QGraphicsLineItem* m_line;
	};
}

#endif //KOMPTON_PARTICLE_H