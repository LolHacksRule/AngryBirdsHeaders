#ifndef ROVIOSHELF_H
#define ROVIOSHELF_H

#include <gr/Color.h>
#include <lang/Event.h>

namespace rcs
{
	class SkynestIdentity;
	class Identity;
};

using namespace gr;

namespace rovioshelf
{
	class RovioShelf
	{
	public:
		enum State
		{
			NOT_LOADED,
			APPEARING,
			DRAGGING,
			COLLAPSING,
			COLLAPSED,
			EXPANDING,
			EXPANDED
		};
		const lang::Event<void(State)> EVENT_STATECHANGED;

		RovioShelf(Context, Identity);

		virtual ~RovioShelf();

		static void setAllowed(bool value);

		void update(float dt);
		void render();

		bool isCapturingInput() const;

		void setInputCapturing(bool value);

	private:
		class Impl;
		P(Impl) m_impl;
	};
};
#endif // !ROVIOSHELF_H