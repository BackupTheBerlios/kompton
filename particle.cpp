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

#include "particle.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QPen>
#include <cmath>

Kompton::Particle::Particle(const QPointF& start, const QPointF& end, QGraphicsItem* parent)
	: QGraphicsPathItem(parent)
	, m_line(start, end)
	, m_style(Kompton::PlainStyle)
{
	setAcceptHoverEvents(true);
	QPen pen(Qt::black);
	pen.setWidth(2);
	setPen(pen);
	rebuildRepresentation();
}

Kompton::Particle::~Particle() {
}

void Kompton::Particle::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (event->button() == Qt::LeftButton)
		emit particleClicked(this);
	else if (event->button() == Qt::RightButton) {
		//DEBUG code to change between particle styles
		switch (m_style) {
			case Kompton::PlainStyle:
				setStyle(Kompton::WigglyStyle);
				break;
			case Kompton::WigglyStyle:
				setStyle(Kompton::PlainStyle);
				break;
		}
	}
}

void Kompton::Particle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	QPen pen(Qt::cyan);
	pen.setWidth(5);
	setPen(pen);
}

void Kompton::Particle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	QPen pen(Qt::black);
	pen.setWidth(2);
	setPen(pen);
}

QLineF Kompton::Particle::line() const
{
	return m_line;
}

void Kompton::Particle::setLine(const QLineF& line) {
	m_line = line;
	rebuildRepresentation();
}

void Kompton::Particle::setLine(const QPointF& start, const QPointF& end) {
	m_line = QLineF(start, end);
	rebuildRepresentation();
}

Kompton::ParticleStyle Kompton::Particle::style() const {
	return m_style;
}

void Kompton::Particle::setStyle(Kompton::ParticleStyle style) {
	m_style = style;
	rebuildRepresentation();
}

void Kompton::Particle::rebuildRepresentation() {
	//prepare a new path
	QPainterPath path;
	path.moveTo(m_line.p1());
	//draw on the path according to the style
	if (m_style == Kompton::PlainStyle) {
		path.lineTo(m_line.p2());
	} else if (m_style == Kompton::WigglyStyle) {
		const QPointF start = m_line.p1();
		const QPointF diff = m_line.p2() - start;
		//some constants of the representation
		static const qreal amplitude = 10.0; //maximum wave elongation
		static const qreal wavelength = 20.0;
		//parameters for this wave
		const qreal waveCount = floor(sqrt(diff.x() * diff.x() + diff.y() * diff.y()) / wavelength);
		const QPointF waveDiff = diff / waveCount;
		const qreal slope = atan2(diff.y(), diff.x());
		const QPointF waveElongationVector(amplitude * -sin(slope), amplitude * cos(slope));
		//draw waves
		for (qreal i = 0.0; i < waveCount; ++i) {
			path.quadTo(start + waveDiff * (i + 0.25) + waveElongationVector, start + waveDiff * (i + 0.5));
			path.quadTo(start + waveDiff * (i + 0.75) - waveElongationVector, start + waveDiff * (i + 1.0));
		}
	}
	//make new path active
	setPath(path);
}

#include "particle.moc"
