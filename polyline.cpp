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

#include <QLineF>

#include "node.h"
#include "polyline.h"

Kompton::PolyLine::PolyLine(const QPointF& start, const QPointF& end)
	: QObject()
{
	QLineF line(start, end);
	m_lineList << line;
}

Kompton::PolyLine::~PolyLine() {
	m_lineList.clear();			//the exact function for the destructor?
}

QLineF Kompton::PolyLine::getLine() {
	return m_lineList.first();
}
