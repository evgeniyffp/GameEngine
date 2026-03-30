#pragma once

namespace GLSetting {
	class Version {
	private:
		static int GlmajorVersion;
		static int GLminorVersion;

	public:
		static void set(int _GlmajorVersion, int _GLminorVersion) {
			GlmajorVersion = _GlmajorVersion;
			GLminorVersion = _GLminorVersion;
		}
		static int majorVersion() { return GlmajorVersion; }
		static int minorVersion() { return GLminorVersion; }
	};

	inline int Version::GlmajorVersion = 4;
	inline int Version::GLminorVersion = 5;
}

