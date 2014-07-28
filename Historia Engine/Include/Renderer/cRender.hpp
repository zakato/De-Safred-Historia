#ifndef CRENDER_H
#define CRENDER_H

#include <Artemis\Component.hpp>



namespace zkt
{

	class cRender : public artemis::Component
	{
	public:
		cRender() : m_isRendering(true) {}
		bool getIsRendering() const { return m_isRendering; }

	private:
		bool m_isRendering;
	};
}

#endif