#pragma once

namespace GLSetting {
	class Version {
	private:
		static int GlmajorerVersion;
		static int GLminorVersion;

	public:
		static void set(int _GlmajorerVersion, int _GLminorVersion) {
			GlmajorerVersion = _GlmajorerVersion;
			GLminorVersion = _GLminorVersion;
		}
		static int majorerVersion() { return GlmajorerVersion; }
		static int minorVersion() { return GLminorVersion; }
	};

	inline int Version::GlmajorerVersion = 4;
	inline int Version::GLminorVersion = 5;
}

