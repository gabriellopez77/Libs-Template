#pragma once

namespace ml {
	class Shader final {
	public:
		Shader(const char* vertPath, const char* fragPath);

		unsigned int id;

		unsigned int colorLoc;
		unsigned int modelLoc;
		unsigned int viewLoc;
		unsigned int alphaLoc;
		unsigned int useTextureLoc;
	};
}