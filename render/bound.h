// Aqsis
// Copyright � 1997 - 2001, Paul C. Gregory
//
// Contact: pgregory@aqsis.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


/** \file
		\brief Declares the geometric boundary handling class.
		\author Paul C. Gregory (pgregory@aqsis.com)
*/

//? Is .h included already?
#ifndef BOUND_H_INCLUDED
#define BOUND_H_INCLUDED 1

#include	"aqsis.h"

#include	"ri.h"
#include	"matrix.h"

#include <vector>

START_NAMESPACE( Aqsis )

//----------------------------------------------------------------------
/** \class CqBound
 * Class specifying a 3D geometric bound.
 */

class CqBound
{
	public:
		CqBound( TqFloat* pBounds )
		{
			if ( pBounds )
			{
				m_vecMin.x( pBounds[ 0 ] );	m_vecMin.y( pBounds[ 1 ] );	m_vecMin.z( pBounds[ 2 ] );
				m_vecMax.x( pBounds[ 3 ] );	m_vecMax.y( pBounds[ 4 ] );	m_vecMax.z( pBounds[ 5 ] );
			}
		}
		CqBound( TqFloat XMin = FLT_MAX, TqFloat YMin = FLT_MAX, TqFloat ZMin = FLT_MAX, TqFloat XMax = -FLT_MAX, TqFloat YMax = -FLT_MAX, TqFloat ZMax = -FLT_MAX )
		{
			m_vecMin.x( XMin );	m_vecMin.y( YMin );	m_vecMin.z( ZMin );
			m_vecMax.x( XMax );	m_vecMax.y( YMax );	m_vecMax.z( ZMax );
		}
		CqBound( const CqVector3D& vecMin, const CqVector3D& vecMax )
		{
			m_vecMin = vecMin;
			m_vecMax = vecMax;
		}
		CqBound( const CqBound& From );
		~CqBound()
		{}

		const	CqVector3D&	vecMin() const
		{
			return ( m_vecMin );
		}
		CqVector3D&	vecMin()
		{
			return ( m_vecMin );
		}
		const	CqVector3D&	vecMax() const
		{
			return ( m_vecMax );
		}
		CqVector3D&	vecMax()
		{
			return ( m_vecMax );
		}
		CqBound&	operator=( const CqBound& From );

		void		Transform( const CqMatrix&	matTransform );
		CqBound		Combine( const CqBound& bound );
		CqBound&	Encapsulate( const CqBound& bound );
		CqBound&	Encapsulate( const CqVector3D& v );
		CqBound&	Encapsulate( const CqVector2D& v );

		TqBool	Contains3D( const CqVector3D& v )
		{
			if ( ( v.x() >= m_vecMin.x() && v.x() <= m_vecMax.x() ) &&
			        ( v.y() >= m_vecMin.y() && v.y() <= m_vecMax.y() ) &&
			        ( v.z() >= m_vecMin.z() && v.z() <= m_vecMax.z() ) )
				return ( TqTrue );
			else
				return ( TqFalse );
		}
		TqBool	Contains2D( const CqVector2D& v )
		{
			if ( ( v.x() < m_vecMin.x() || v.x() > m_vecMax.x() ) ||
			        ( v.y() < m_vecMin.y() || v.y() > m_vecMax.y() ) )
				return ( TqFalse );
			else
				return ( TqTrue );
		}

	private:
		CqVector3D	m_vecMin;
		CqVector3D	m_vecMax;
};

//----------------------------------------------------------------------
/** \class CqBoundList
 * Class specifying a list of CqBounds.
 */
class CqBoundList
{
	public:
		CqBoundList()
		{}
		~CqBoundList()
		{
			//for ( std::vector<CqBound*>::iterator i = m_Bounds.begin(); i != m_Bounds.end(); i++ )
			//	delete ( *i );
		}

		/** Clear the list
		 */
		void Clear()
		{
			//for ( std::vector<CqBound*>::iterator i = m_Bounds.begin(); i != m_Bounds.end(); i++ )
			//	delete ( *i );
			m_Bounds.clear();
			m_Times.clear();
		}

		void SetSize( TqInt size )
		{
			m_Bounds.resize( size );
			m_Times.resize( size );
		}
		/** Add a bound to the current list
		 * \param index The index to set in the list.
		 * \param bound The CqBound to add
		 * \param time The shutter time that this bound becomes valid at. The bound
		 *               is valid until the time of the next bound or until 1.0 if there are no more bounds.
		 */
		void	Set( TqInt index, CqBound bound, TqFloat time )
		{
			assert( index < Size() );
			m_Bounds[ index ] = bound;
			m_Times[ index ] = time;
		}
		TqInt Size()
		{
			return m_Bounds.size();
		}

		CqBound& GetBound( TqInt i )
		{
			return m_Bounds[ i ];
		}
		TqFloat GetTime( TqInt i )
		{
			return m_Times[ i ];
		}

	private:
		std::vector<CqBound> m_Bounds;
		std::vector<TqFloat> m_Times;
};

//-----------------------------------------------------------------------

END_NAMESPACE( Aqsis )

#endif // BOUND_H_INCLUDED
